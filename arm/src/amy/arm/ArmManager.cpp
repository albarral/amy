/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include "log4cxx/ndc.h"

#include "amy/arm/ArmManager.h"
#include "amy/arm/config/ArmConfig.h"
#include "amy/arm/config/ArmDefines.h"
#include "amy/arm/bus/ArmBus.h"


using namespace log4cxx;

namespace amy
{
LoggerPtr ArmManager::logger(Logger::getLogger("amy.arm"));

// Constructor
ArmManager::ArmManager ()
{    
    benabled = false;
    level = 0;
}

// Destructor
ArmManager::~ArmManager ()
{
}

void ArmManager::init(std::string robotName)
{
    log4cxx::NDC::push("Arm Manager");   	
    
    LOG4CXX_INFO(logger, "INITIALIZING ... ");
    
    if (oArmConfig.loadRobot(robotName) == false)
        LOG4CXX_ERROR(logger, "Not enabled !!! Robot not supported: " + robotName);
    
    // obtain (from config file) the list of joints to be controlled 
    std::vector<std::string>& listJointNames = oArmConfig.getListJointNames();

    initArm(listJointNames);
    initBus(listJointNames);
    initModules(listJointNames);

    // TEMP: first soll angles are 0 (should be the ist)
    for (int i=0; i<AMY_MAX_JOINTS; i++ )
        listSollAngles.push_back(0);    
   
    benabled = true;    
}


void ArmManager::initArm(std::vector<std::string>& listJointNames)
{
    LOG4CXX_INFO(logger, ">> INIT Arm ...");
    
    // build arm with joints
    int numJoints = listJointNames.size();
    for (int i=0; i<numJoints; i++)
    {        
        std::string jointName = listJointNames.at(i);        
        LOG4CXX_INFO(logger, jointName);
        
        // arm's joint
        ParamsJoint& mParamsJoint = oArmConfig.getParamsJoint(jointName);                        
        Joint oJoint; 
        oJoint.init(mParamsJoint);    
        oArm.addJoint(oJoint);                
    }
}


void ArmManager::initBus(std::vector<std::string>& listJointNames)
{
    LOG4CXX_INFO(logger, ">> INIT Bus ...");
    
    // setup connections for each joint
    int numJoints = listJointNames.size();
    for (int i=0; i<numJoints; i++)
    {        
        std::string jointName = listJointNames.at(i);        
        LOG4CXX_INFO(logger, jointName);
        
        if (oArmBus.addJointBus(jointName) == false)
        {
            LOG4CXX_ERROR(logger, "Error adding bus connection for joint " << jointName);
            return;
        }
    }
}

void ArmManager::initModules(std::vector<std::string>& listJointNames)
{    
    float freq = oArmConfig.getModulesFreq();

    // init modules FOR each joint
    int numJoints = listJointNames.size();
    
    LOG4CXX_INFO(logger, ">> INIT modules ... level " << level);
    // joint control modules
    for (int i=0; i<numJoints; i++)
    {        
        std::string jointName = listJointNames.at(i);        
        // bus connections for this joint
        JointBus& oJointBus = oArmBus.getJointBus(jointName);

        Joint& mJoint = oArm.getJointByName(jointName);
        oJointControl[i].init(jointName, mJoint);  
        oJointControl[i].connect(oJointBus);
        oJointControl[i].setFrequency(freq);           
    }
    usleep(200000);
    
    level++;
    LOG4CXX_INFO(logger, ">> INIT modules ... level " << level);       
    // joint mover modules
    for (int i=0; i<numJoints; i++)
    {        
        std::string jointName = listJointNames.at(i);        
        // bus connections for this joint
        JointBus& oJointBus = oArmBus.getJointBus(jointName);

        ParamsJointMover& mParamsJointMover = oArmConfig.getParamsJointMover(jointName);        
        oJointMover[i].init(jointName, mParamsJointMover);  
        oJointMover[i].connect(oJointBus);
        oJointMover[i].setFrequency(freq);
    }
    usleep(200000);

    level++;
    LOG4CXX_INFO(logger, ">> INIT modules ... level " << level);       
    // arm mover module
    oArmMover.init(3000);
    oArmMover.connect(oArmBus);
    oArmMover.setFrequency(freq);
    usleep(500000);
    
    level++;
    LOG4CXX_INFO(logger, ">> INIT modules ... level " << level);       
    // coms in module
    oArmComs.init();
    oArmComs.connect(oArmBus);
    oArmComs.setFrequency(freq);  
    // coms out module
    oArmComsOut.init(numJoints);
    oArmComsOut.connect(oArmBus);
    oArmComsOut.setFrequency(freq);  // set to slower 3Hz because it uses a DB network  
}


void ArmManager::startModules()
{
    LOG4CXX_INFO(logger, "STARTING MODULES ...");
    level = 0;

    if (!benabled)
        return;

    int numJoints = oArmConfig.getNumJoints();    
    
    LOG4CXX_INFO(logger, ">> START level " << level);
   // joint control modules
   for (int i=0; i<numJoints; i++)
    {
        if (oJointControl[i].isEnabled() && oJointControl[i].isConnected())
            oJointControl[i].on();
    }

    level++;
    LOG4CXX_INFO(logger, ">> START level " << level);
   // joint mover modules
   for (int i=0; i<numJoints; i++)
    {
        if (oJointMover[i].isEnabled() && oJointMover[i].isConnected())
            oJointMover[i].on();
    }
    
    level++;
    LOG4CXX_INFO(logger, ">> START level " << level);
    // arm mover module
    if (oArmMover.isEnabled() && oArmMover.isConnected())
        oArmMover.on();

    level++;
    LOG4CXX_INFO(logger, ">> START level " << level);
    // coms in module
    if (oArmComs.isEnabled() && oArmComs.isConnected())
        oArmComs.on();
    // coms out module
    if (oArmComsOut.isEnabled() && oArmComsOut.isConnected())
        oArmComsOut.on();

}

void ArmManager::stopModules()
{    
    LOG4CXX_INFO(logger, "STOPPING MODULES ...");

    if (!benabled)
        return;

    int numJoints = oArmConfig.getNumJoints();    

    LOG4CXX_INFO(logger, ">> STOP level " << level);
    // coms out module
    oArmComsOut.off();
    oArmComsOut.wait();
    // coms in module
    oArmComs.off();
    oArmComs.wait();

    level--;
    LOG4CXX_INFO(logger, ">> STOP level " << level);
    // arm mover module
    oArmMover.off();
    oArmMover.wait();

    level--;
    LOG4CXX_INFO(logger, ">> STOP level " << level);
    // joint mover modules
    for (int i=0; i<numJoints; i++)
    {
        // stop & wait for modules 
        if (oJointMover[i].isEnabled())
        {
            oJointMover[i].off();
            oJointMover[i].wait();
        }
    }

    level--;
    LOG4CXX_INFO(logger, ">> STOP level " << level);
    // joint control modules
    for (int i=0; i<numJoints; i++)
    {
        // stop & wait for modules 
        if (oJointControl[i].isEnabled()) 
        {
            oJointControl[i].off();
            oJointControl[i].wait();
        }
    }       
}


// Writes to bus
void ArmManager::setIstAngles(std::vector<float>& listAngles)
{
    int size = listAngles.size();
    
    for (int i=0; i<size; i++)
    {
        // write angle in SI_ANGLE
        JointBus& oJointBus = mapBus2SystemIO(i);
        oJointBus.getSO_IST_ANGLE().setValue(listAngles.at(i));
    }            
}


// Reads from bus
void ArmManager::readSollAngles()
{        
    int numJoints = oArmConfig.getNumJoints();       
    
    // for each joint, check if the commanded angle has changed & insert it into the soll list
    for (int i=0; i<numJoints; i++)
    {      
        JointBus& oJointBus = mapBus2SystemIO(i);
        if (oJointBus.getCO_JOINT_ANGLE().checkRequested())
        {
            listSollAngles[i] = oJointBus.getCO_JOINT_ANGLE().getValue();
        }
    }
}

JointBus& ArmManager::mapBus2SystemIO(int i)
{
    switch (i)
    {
        case 0:
            return oArmBus.getBusHS();
            break;
        case 1:
            return oArmBus.getBusVS();
            break;
        case 2:
            return oArmBus.getBusEL();
            break;
        case 3:
            return oArmBus.getBusVW();
            break;
        case 4:
            return oArmBus.getBusHW();
            break;
        // for invalid indexes return the HS           
        default:
            return oArmBus.getBusHS();
            break;
    }
    
}

bool ArmManager::checkEndRequested()
{
    return oArmBus.getCO_FINISH_MANAGER().checkRequested();
}

}




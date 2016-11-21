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
#include "amy/robot/SupportedRobots.h"
#include "amy/robot/Robot.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmManager::logger(Logger::getLogger("amy.arm"));

// Constructor
ArmManager::ArmManager ()
{    
    benabled = false;
    level = -1;
    maxLevel = 3;
}

// Destructor
ArmManager::~ArmManager ()
{
}


bool ArmManager::launch(Robot& oRobot, int targetArm) 
{  
    bool bok = false;
    log4cxx::NDC::push("ArmManager-" + std::to_string(targetArm));   	
    
    // get target arm to control
    Arm* pArm = oRobot.getArmByType(targetArm);
    // target arm not found
    if (pArm != 0)
    {
        LOG4CXX_INFO(logger, "Launching for arm type " << targetArm);
        oArm = *pArm;
        // init modules & start them
        init();
        if (benabled)
        {
            startModules();
            bok = true;
        }
    }
    // target arm not found
    else
    {
        LOG4CXX_WARN(logger, "No arm type " << targetArm << " found for robot. Launch failed.");
        return false;
    }
    
    return bok;
}

bool ArmManager::end()
{
    stopModules();
}

void ArmManager::init()
{        
    LOG4CXX_INFO(logger, "INITIALIZING ... (max level " << maxLevel << ")");

    // organize control architecture in levels
    initArchitecture();
    showArchitecture();
    
    // obtain (from config file) the list of joints to be controlled 
    std::vector<std::string>& listControlledJoints = oArmConfig.getListControlledJoints();

    // set params for movement
    oMovementControl.setKaccelDriver(4.0);
    oMovementControl.setKspeedDriver(2.0);
    oMovementControl.setDriverTolerance(0.05);
    oMovementControl.setDriverSpeed(60.0);
    initBus(listControlledJoints);
    initModules();

    // TEMP: first soll angles are 0 (should be the ist)
    for (int i=0; i<AMY_MAX_JOINTS; i++ )
        listSollAngles.push_back(0);    
   
    benabled = true;    
}

void ArmManager::initArchitecture()
{
    std::vector<std::string>& listControlledJoints = oArmConfig.getListControlledJoints();
    int nivel, i;

    // LEVEL 0
    nivel = 0;
    // coms in module
    oArmComs.setLevel(nivel);
    listModules.push_back(&oArmComs);
    // coms out module
    oArmComsOut.setLevel(nivel);
    listModules.push_back(&oArmComsOut);

    // LEVEL 1    
    nivel = 1;
    // joint control modules
    i=0;
    for (std::string& jointName : listControlledJoints)
    {        
        oJointControl2[i].setTargetJoint(jointName);        
        oJointControl2[i].setLevel(nivel);
        listModules.push_back(&oJointControl2[i]);
        i++;
    }
    
    // LEVEL 2    
    nivel = 2;
    // joint mover modules
    i=0;
    for (std::string& jointName : listControlledJoints)
    {        
        // removed JointMover modules
        i++;
    }

    // LEVEL 3    
    nivel = 3;        
    // arm mover module
    oArmMover.setLevel(nivel);     
    listModules.push_back(&oArmMover);
    // arm panner module
    oArmPanner.setLevel(nivel);
    //listModules.push_back(&oArmPanner);   // it's a module3, not a module2
    // arm elbow module
    oArmElbow.setLevel(nivel);
    //listModules.push_back(&oArmElbow);   // it's a module3, not a module2
    // arm extender            
    oArmExtender.setLevel(nivel);
    //listModules.push_back(&oArmExtender); // it's a module3, not a module2
}

void ArmManager::showArchitecture()
{
    LOG4CXX_INFO(logger, ">> control architecture ...");
    for (ArmModule* pModule : listModules)
    {
        LOG4CXX_INFO(logger, "level " << std::to_string(pModule->getLevel()) << ": module " << pModule->getModuleName());        
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
    
    LOG4CXX_INFO(logger, oArmBus.toString());
}

void ArmManager::initModules()
{    
    LOG4CXX_INFO(logger, "INIT MODULES ...");

    level = -1;
    for (int i=0; i<=maxLevel; i++)
    {
        initLevel(i);
        level = i;        
    }
}

void ArmManager::startModules()
{
    LOG4CXX_INFO(logger, "STARTING MODULES ...");

    if (!benabled)
        return;
    
    level = -1;
    int microsWait = 100000;  // 100ms
    for (int i=0; i<=maxLevel; i++)
    {
        startLevel(i);
        level = i;        
        usleep(microsWait);
    }
}

void ArmManager::stopModules()
{    
    LOG4CXX_INFO(logger, "STOPPING MODULES ...");

    if (!benabled)
        return;

    for (int i=level; i>=0; i--)
    {
        stopLevel(i);
        level = i;        
    }
}

void ArmManager::initLevel(int num)
{    
    LOG4CXX_INFO(logger, ">> INIT level " << num);       

    float freq = oArmConfig.getModulesFreq();

    for (ArmModule* pModule : listModules)
    {
        if (pModule->getLevel() == num)
        {                        
            pModule->init(oArm);
            pModule->connect(oArmBus);
            pModule->setFrequency(freq);  
        }
    }

    if (oArmPanner.getLevel() == num)
    {    
        // arm panner module
        oArmPanner.init(oArm, oMovementControl);
        oArmPanner.connect(oArmBus);
        oArmPanner.setFrequency(freq);
    }
    
    if (oArmElbow.getLevel() == num)
    {    
        // arm panner module
        oArmElbow.init(oArm, oMovementControl);
        oArmElbow.connect(oArmBus);
        oArmElbow.setFrequency(freq);
    }

    if (oArmExtender.getLevel() == num)
    {
        // arm extender module
        oArmExtender.init(oMovementControl);
        oArmExtender.connect(oArmBus);
        oArmExtender.setFrequency(freq);
        oArmExtender.tune2Arm(oArm.getLenHumerus(), oArm.getLenRadius());            
    }    
}

void ArmManager::startLevel(int num)
{
    LOG4CXX_INFO(logger, ">> START level " << num);

    for (ArmModule* pModule : listModules)
    {
        if (pModule->getLevel() == num)
        {
            if (pModule->isEnabled() && pModule->isConnected())
                pModule->on();
        }
    }

    if (oArmPanner.getLevel() == num)
    {    
        if (oArmPanner.isEnabled() && oArmPanner.isConnected())      
            oArmPanner.on();                      
    }
    
    if (oArmElbow.getLevel() == num)
    {    
        if (oArmElbow.isEnabled() && oArmElbow.isConnected())      
            oArmElbow.on();                      
    }

    if (oArmExtender.getLevel() == num)
    {
        // arm extender module
        if (oArmExtender.isEnabled() && oArmExtender.isConnected())
        {
            oArmExtender.on();          
            oArmExtender.senseInitialPosition();
        }
    }
}

void ArmManager::stopLevel(int num)
{
    LOG4CXX_INFO(logger, ">> STOP level " << num);
       
    for (ArmModule* pModule : listModules)
    {
        if (pModule->getLevel() == num)
        {
            if (pModule->isEnabled())
            {
                pModule->off();
                pModule->wait();
            }
        }
    }

    if (oArmPanner.getLevel() == num)
    {    
        oArmPanner.off();
        oArmPanner.wait();
    }
    
    if (oArmElbow.getLevel() == num)
    {    
        oArmElbow.off();
        oArmElbow.wait();
    }

    if (oArmExtender.getLevel() == num)
    {
        // arm extender module
        oArmExtender.off();
        oArmExtender.wait();
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
    int numJoints = oArmConfig.getNumControlledJoints();       
    
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




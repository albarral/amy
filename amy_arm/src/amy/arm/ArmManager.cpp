/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include "log4cxx/ndc.h"

#include "amy/arm/ArmManager.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmManager::logger(Logger::getLogger("amy.arm"));

// Constructor
ArmManager::ArmManager ()
{    
    blaunched = false;
    level = -1;
    maxLevel = 3;
    pAmyConfig = 0;
    pArmBus = 0;
}

// Destructor
ArmManager::~ArmManager ()
{
    listModules.clear();
}


bool ArmManager::launch(AmyConfig& oAmyConfig, ArmBus& oArmBus, Arm& oTargetArm) 
{  
    // launch it if not launched yet and bus enabled
    if (!blaunched && oArmBus.isEnabled())
    {
        log4cxx::NDC::push("ArmManager-" + std::to_string(oTargetArm.getType()));   	
        LOG4CXX_INFO(logger, "Launching for arm type " << oTargetArm.getType());

        // acces to amy config
        pAmyConfig = &oAmyConfig;
        // access arm bus 
        pArmBus = &oArmBus;
        oArm = oTargetArm;

        // init modules & start them
        LOG4CXX_INFO(logger, "max level: " << maxLevel);
        // organize control architecture in levels
        initArchitecture();
        showArchitecture();

        initModules();
        startModules();

        blaunched = true;    
    }
    // report problems
    else
    {
        if (blaunched)
            LOG4CXX_ERROR(logger, "Can't launch ArmManager: already launched!");
        
        if (!oArmBus.isEnabled())
            LOG4CXX_ERROR(logger, "Can't launch ArmManager: arm bus not enabled!");                    
    }
    
    return blaunched;
}

bool ArmManager::end()
{
    stopModules();
}

void ArmManager::initArchitecture()
{
    std::vector<std::string>& listControlledJoints = pAmyConfig->getListControlledJoints();
    int nivel, i;

    // LEVEL 0
    nivel = 0;
    // nothing
    
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
    oArmElbow.setLevel(1000); // disabled, as it collides with ArmExtender
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

    if (!blaunched)
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

    if (!blaunched)
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

    float freq = pAmyConfig->getModulesFreq();

    for (ArmModule* pModule : listModules)
    {
        if (pModule->getLevel() == num)
        {                        
            pModule->init(oArm, pAmyConfig->getJointControlConfig());
            pModule->connect(pArmBus);
            pModule->setFrequency(freq);  
        }
    }

    if (oArmPanner.getLevel() == num)
    {    
        // arm panner module
        oArmPanner.init(oArm, pAmyConfig->getJointControlConfig());
        oArmPanner.connect(pArmBus);
        oArmPanner.setFrequency(freq);
    }
    
    if (oArmElbow.getLevel() == num)
    {    
        // arm panner module
        oArmElbow.init(oArm, pAmyConfig->getJointControlConfig());
        oArmElbow.connect(pArmBus);
        oArmElbow.setFrequency(freq);
    }

    if (oArmExtender.getLevel() == num)
    {
        // arm extender module
        oArmExtender.init(oArm, pAmyConfig->getJointControlConfig());
        oArmExtender.connect(pArmBus);
        oArmExtender.setFrequency(freq);
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

}




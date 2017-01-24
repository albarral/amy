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
    maxLevel = 2;       
    pAmyConfig = 0;
}

// Destructor
ArmManager::~ArmManager ()
{
    listModules.clear();
}


bool ArmManager::launch(AmyConfig& oAmyConfig, Arm& oTargetArm) 
{  
    // launch it if not launched yet
    if (!blaunched)
    {
        log4cxx::NDC::push("ArmManager-" + std::to_string(oTargetArm.getType()));   	
        LOG4CXX_INFO(logger, "Launching for arm type " << oTargetArm.getType());

        // acces to amy config
        pAmyConfig = &oAmyConfig;
        oArm = oTargetArm;
        
        // init bus & connect arm interface to it
        oArmBus.init(oArm);
        oArmInterface.connect(oArmBus);
        
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
    
    // LEVEL 1    
    nivel = 1;
    // joint control modules
    i=0;
    for (std::string& jointName : listControlledJoints)
    {        
        oJointDriver[i].setTargetJoint(jointName);        
        oJointDriver[i].setLevel(nivel);
        listModules.push_back(&oJointDriver[i]);
        i++;
    }
    
    // LEVEL 2    
    nivel = 2;        
    // arm mover module
    //oArmMover.setLevel(nivel);     
    //listModules.push_back(&oArmMover);
    // pan driver module
    oPanDriver.setLevel(nivel);
    //listModules.push_back(&oPanDriver);   // it's a module3, not a module2
    // tilt driver module
    oTiltDriver.setLevel(nivel);
    //listModules.push_back(&oPanDriver);   // it's a module3, not a module2
    // arm elbow module
    oRadiusDriver.setLevel(nivel); 
    //listModules.push_back(&oRadiusDriver);   // it's a module3, not a module2
    // arm extender            
    oArmExtender.setLevel(1000);    // DISABLED!! as it collides with tilt & radius drivers
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
            pModule->connect(oArmBus);
            pModule->setFrequency(freq);  
        }
    }

    if (oPanDriver.getLevel() == num)
    {    
        // pan driver module
        oPanDriver.init(oArm, pAmyConfig->getJointControlConfig());
        oPanDriver.connect(oArmBus);
        oPanDriver.setFrequency(freq);
    }
    
    if (oTiltDriver.getLevel() == num)
    {    
        // tilt driver module
        oTiltDriver.init(oArm, pAmyConfig->getJointControlConfig());
        oTiltDriver.connect(oArmBus);
        oTiltDriver.setFrequency(freq);
    }

    if (oRadiusDriver.getLevel() == num)
    {    
        // pan driver module
        oRadiusDriver.init(oArm, pAmyConfig->getJointControlConfig());
        oRadiusDriver.connect(oArmBus);
        oRadiusDriver.setFrequency(freq);
    }

    if (oArmExtender.getLevel() == num)
    {
        // arm extender module
        oArmExtender.init(oArm, pAmyConfig->getJointControlConfig());
        oArmExtender.connect(oArmBus);
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

    if (oPanDriver.getLevel() == num)
    {    
        if (oPanDriver.isEnabled() && oPanDriver.isConnected())      
            oPanDriver.on();                      
    }

    if (oTiltDriver.getLevel() == num)
    {    
        if (oTiltDriver.isEnabled() && oTiltDriver.isConnected())      
            oTiltDriver.on();                      
    }
    
    if (oRadiusDriver.getLevel() == num)
    {    
        if (oRadiusDriver.isEnabled() && oRadiusDriver.isConnected())      
            oRadiusDriver.on();                      
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
            if (pModule->isOn())
            {
                pModule->off();
                pModule->wait();
            }
        }
    }

    if (oPanDriver.getLevel() == num && oPanDriver.isOn())
    {    
        oPanDriver.off();
        oPanDriver.wait();
    }
    
    if (oTiltDriver.getLevel() == num && oTiltDriver.isOn())
    {    
        oTiltDriver.off();
        oTiltDriver.wait();
    }

    if (oRadiusDriver.getLevel() == num && oRadiusDriver.isOn())
    {    
        oRadiusDriver.off();
        oRadiusDriver.wait();
    }

    if (oArmExtender.getLevel() == num && oArmExtender.isOn())
    {
        // arm extender module
        oArmExtender.off();
        oArmExtender.wait();
    }
}

}




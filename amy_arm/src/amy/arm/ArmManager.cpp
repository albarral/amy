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
        LOG4CXX_INFO(logger, "Launching for arm " << oTargetArm.toString());

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
        
        // for test, activate TiltKeeper module
        bool keepMode = true;
        oArmBus.getCO_KEEP_TILT().request(keepMode);

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
    
    // arm polar sensing module
    oArmPolarSensing.setLevel(nivel);
    // pan driver module
    oPanDriver.setLevel(nivel);
    // tilt driver module
    oTiltDriver.setLevel(nivel);
    // arm elbow module
    oRadiusDriver.setLevel(nivel); 
    // tilt keeper module
    oTiltKeeper.setLevel(nivel);
    //listModules.push_back(&oArmPolarSensing);   // it's an ArmModule3

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
            pModule->init(oArm, oArmConfig);
            pModule->connect(oArmBus);
            pModule->setFrequency(freq);  
        }
    }

    if (oArmPolarSensing.getLevel() == num)
    {
        // arm position module 
        oArmPolarSensing.init(oArm, oArmConfig);
        oArmPolarSensing.connect(oArmBus);
        oArmPolarSensing.setFrequency(freq);
    }    

    if (oPanDriver.getLevel() == num)
    {    
        // pan driver module
        oPanDriver.init(oArm, oArmConfig);
        oPanDriver.connect(oArmBus);
        oPanDriver.setFrequency(freq);
    }
    
    if (oTiltDriver.getLevel() == num)
    {    
        // tilt driver module
        oTiltDriver.init(oArm, oArmConfig);
        oTiltDriver.connect(oArmBus);
        oTiltDriver.setFrequency(freq);
    }

    if (oRadiusDriver.getLevel() == num)
    {    
        // pan driver module
        oRadiusDriver.init(oArm, oArmConfig);
        oRadiusDriver.connect(oArmBus);
        oRadiusDriver.setFrequency(freq);
    }

    if (oTiltKeeper.getLevel() == num)
    {
        // arm extender module
        oTiltKeeper.init(oArm, oArmConfig);
        oTiltKeeper.connect(oArmBus);
        oTiltKeeper.setFrequency(freq);
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

    if (oArmPolarSensing.getLevel() == num)
    {
        if (oArmPolarSensing.isEnabled() && oArmPolarSensing.isConnected())
        {
            oArmPolarSensing.on();          
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

    if (oTiltKeeper.getLevel() == num)
    {
        if (oTiltKeeper.isEnabled() && oTiltKeeper.isConnected())
            oTiltKeeper.on();          
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

    if (oArmPolarSensing.getLevel() == num && oArmPolarSensing.isOn())
    {
        oArmPolarSensing.off();
        oArmPolarSensing.wait();
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

    if (oTiltKeeper.getLevel() == num && oTiltKeeper.isOn())
    {
        oTiltKeeper.off();
        oTiltKeeper.wait();
    }
}

}




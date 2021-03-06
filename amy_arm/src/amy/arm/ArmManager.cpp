/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include "log4cxx/ndc.h"

#include "amy/arm/ArmManager.h"
#include "amy/core/robot/Arm.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmManager::logger(Logger::getLogger("amy.arm"));

// Constructor
ArmManager::ArmManager ()
{    
    blaunched = false;
    topLevel = 4;       
    pArm = 0; 
    pArmBus = 0;       
}

// Destructor
ArmManager::~ArmManager ()
{
    listModules.clear();
}


bool ArmManager::launch(ArmBus& oArmBus, Arm& oArm) 
{  
    // launch it if not launched yet
    if (!blaunched)
    {
        log4cxx::NDC::push("ArmManager-" + std::to_string(oArm.getType()));   	
        LOG4CXX_INFO(logger, "Launching for arm " << oArm.toString());

        // store pointers to external objects
        pArmBus = &oArmBus;        
        pArm = &oArm;
                
        LOG4CXX_INFO(logger, "top level: " << topLevel);
        // organize control architecture in levels
        initArchitecture();
        showArchitecture();
        // init modules & start them
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
    
    return true;    
}

void ArmManager::initArchitecture()
{
    std::vector<int>& listControlledJoints = oAmyConfig.getListControlledJoints();
    int nivel, i;
    
    // LEVEL 1    
    nivel = 1;
    // joint control modules
    i=0;
    for (int jointType : listControlledJoints)
    {        
        oJointDriver[i].setTargetJoint(jointType);        
        oJointDriver[i].setLevel(nivel);
        listModules.push_back(&oJointDriver[i]);
        i++;
    }
    
    // LEVEL 2    
    nivel = 2;        
    
    // arm sense module
    oArmSense.setLevel(nivel);
    listModules3.push_back(&oArmSense);

    // pan / tilt / radius driver modules
    oPanDriver.setLevel(nivel);
    oTiltDriver.setLevel(nivel);
    oRadiusDriver.setLevel(nivel); 

    // tilt keeper module
    oTiltKeeper.setLevel(nivel);
    listModules3.push_back(&oTiltKeeper);

    // LEVEL 3    
    nivel = 3;        

    // pan / tilt / radial racer modules
    oPanRacer.setLevel(nivel);
    oTiltRacer.setLevel(nivel);
    oRadialRacer.setLevel(nivel);
    oPanRacer.setTargetAxis(Arm::eAXIS_PAN);
    oTiltRacer.setTargetAxis(Arm::eAXIS_TILT);
    oRadialRacer.setTargetAxis(Arm::eAXIS_RADIAL);    
    listModules3.push_back(&oPanRacer);
    listModules3.push_back(&oTiltRacer);
    listModules3.push_back(&oRadialRacer);

    // LEVEL 4    
    nivel = 4;        

    // arm cyclers 1 & 2
    oArmCycler1.setLevel(nivel);
    oArmCycler2.setLevel(nivel);
    oArmCycler1.setCyclerId(AmyConfig::CYCLER1);
    oArmCycler2.setCyclerId(AmyConfig::CYCLER2);
    listModules3.push_back(&oArmCycler1);
    listModules3.push_back(&oArmCycler2);
}

void ArmManager::showArchitecture()
{
    LOG4CXX_INFO(logger, ">> control architecture ...");
    for (ArmModule* pModule : listModules)
    {
        LOG4CXX_INFO(logger, "level " << std::to_string(pModule->getLevel()) << ": module " << pModule->getModuleName());        
    }        
    for (ArmModule3* pModule3 : listModules3)
    {
        LOG4CXX_INFO(logger, "level " << std::to_string(pModule3->getLevel()) << ": module " << pModule3->getModuleName());        
    }        
}

void ArmManager::initModules()
{    
    LOG4CXX_INFO(logger, "INIT MODULES ...");

    for (int i=0; i<=topLevel; i++)
    {
        initLevel(i);
    }
}

void ArmManager::startModules()
{
    LOG4CXX_INFO(logger, "STARTING MODULES ...");

    int microsWait = 100000;  // 100ms
    for (int i=0; i<=topLevel; i++)
    {
        startLevel(i);
        usleep(microsWait);
    }
}

void ArmManager::stopModules()
{    
    LOG4CXX_INFO(logger, "STOPPING MODULES ...");

    if (!blaunched)
        return;

    for (int i=topLevel; i>=0; i--)
    {
        stopLevel(i);
    }
}

void ArmManager::initLevel(int num)
{    
    LOG4CXX_INFO(logger, ">> INIT level " << num);       

    float freq = oAmyConfig.getModulesFreq();

    Arm& oArm = *pArm;
    ArmBus& oArmBus = *pArmBus;
    
    // init ArmModule's
    for (ArmModule* pModule : listModules)
    {
        if (pModule->getLevel() == num)
        {                        
            pModule->init(oArm, oArmConfig);
            pModule->connect(oArmBus);
            pModule->setFrequency(freq);  
        }
    }

    // init ArmModule3's
    for (ArmModule3* pModule3 : listModules3)
    {
        if (pModule3->getLevel() == num)
        {
            pModule3->init(oArm, oArmConfig);
            pModule3->connect(oArmBus);
            pModule3->setFrequency(freq);
        }    
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
}

void ArmManager::startLevel(int num)
{
    LOG4CXX_INFO(logger, ">> START level " << num);

    // init ArmModule's
    for (ArmModule* pModule : listModules)
    {
        if (pModule->getLevel() == num)
        {
            if (pModule->isEnabled() && pModule->isConnected())
                pModule->on();
        }
    }

    // init ArmModule3's
    for (ArmModule3* pModule3 : listModules3)
    {
        if (pModule3->getLevel() == num)
        {
            if (pModule3->isEnabled() && pModule3->isConnected())
                pModule3->on();
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
}

void ArmManager::stopLevel(int num)
{
    LOG4CXX_INFO(logger, ">> STOP level " << num);

    // stop ArmModule's
    for (ArmModule* pModule : listModules)
    {
        if (pModule->getLevel() == num && pModule->isOn())
        {            
            pModule->off();
            pModule->wait();
        }
    }

    // stop ArmModule3's
    for (ArmModule3* pModule3 : listModules3)
    {
        if (pModule3->getLevel() == num && pModule3->isOn())
        {
            pModule3->off();
            pModule3->wait();
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
}

}




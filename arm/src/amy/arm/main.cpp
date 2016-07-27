/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include <vector>
#include <string>
#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "amy/arm/ArmManager.h"
#include "amy/network/ArmNetwork.h"
#include "amy/network/ArmData.h"


void launchManipulation();
void testAmyNetwork();

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("amy.arm"));

// main program
int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
    
    //launchManipulation();
    testAmyNetwork();
      
    return 0;
}

void launchManipulation()
{
    LOG4CXX_INFO(logger, "\n\nLAUNCH amy MANIPULATION ...\n");
    
    std::vector<float> listPrevAngles;
    
    amy::ArmManager oArmManager; 
    oArmManager.init("UR5");
    if (!oArmManager.isEnabled())
        return;
    
    oArmManager.startModules();
    
    while (!oArmManager.checkEndRequested()) 
    {
        oArmManager.readSollAngles();
        std::vector<float>& listSollAngles = oArmManager.getSollAngles();
        
        if (listSollAngles != listPrevAngles)
        {
            LOG4CXX_INFO(logger,"moved angles: " << (int)listSollAngles.at(0) << ", " << (int)listSollAngles.at(1) << ", " << (int)listSollAngles.at(2) << ", " << (int)listSollAngles.at(3));      
            listPrevAngles = listSollAngles;            
        }

        sleep(1);
    }    
    
    oArmManager.stopModules();

    return;
}

void testAmyNetwork()
{
    LOG4CXX_INFO(logger, "\n\n<<<<<<<<<<<<<<<< TEST AMY NETWORK >>>>>>>>>>>>>>");      

    // initialize arm network
    amy::ArmNetwork oArmNetwork;
    oArmNetwork.init(amy::ArmNetwork::eNETWORK_DB);

    amy::ArmData oArmData1;
    amy::ArmData oArmData2;
    oArmData1.reset();
    oArmData2.reset();
    oArmData1.setSoll1(11.5);
    oArmData1.setSoll2(12.5);
    oArmData1.setSoll3(13.5);
    oArmData1.setSoll4(14.5);
    oArmData1.setSoll5(15.5);
    oArmData1.setIst1(21.5);
    oArmData1.setIst2(22.5);
    oArmData1.setIst3(23.5);
    oArmData1.setIst4(24.5);
    oArmData1.setIst5(25.5);
    
    LOG4CXX_INFO(logger, oArmData1.toString());
    
    oArmNetwork.setArmSoll(0, oArmData1);
    oArmNetwork.setArmIst(0, oArmData1);
    
    oArmNetwork.getArmSoll(0, oArmData2);
    oArmNetwork.getArmIst(0, oArmData2);
    
    LOG4CXX_INFO(logger, oArmData2.toString());
    
    LOG4CXX_INFO(logger, "TEST FINISHED");      
}
  
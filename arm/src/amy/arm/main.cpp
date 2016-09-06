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

// test amy network
//#include "amy/network/ArmNetwork.h"
//#include "amy/network/ArmData.h"

// test arm planner
#include "amy/arm/modules/ArmComputer.h"
#include "amy/arm/data/MoveStep.h"


void launchManipulation();

void testArmPlanner();
void testAmyNetwork2();
void writePos(amy::ArmNetwork& oArmNetwork, int value);
void readPos(amy::ArmNetwork& oArmNetwork);

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("amy.arm"));

// main program
int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
    	
    launchManipulation();
    //testAmyNetwork2();
    //testArmPlanner();
      
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
            //LOG4CXX_INFO(logger,"moved angles: " << (int)listSollAngles.at(0) << ", " << (int)listSollAngles.at(1) << ", " << (int)listSollAngles.at(2) << ", " << (int)listSollAngles.at(3));      
            listPrevAngles = listSollAngles;            
        }

        sleep(1);
    }    
    
    oArmManager.stopModules();

    return;
}

void testArmPlanner()
{
    amy::Movement oMovement;
    int maxSpeed = 40;    
    
    amy::MoveStep oStep1(30, 5000, maxSpeed);
    amy::MoveStep oStep2(45, 5000, maxSpeed);
    amy::MoveStep oStep3(60, 5000, maxSpeed);
    amy::MoveStep oStep4(89, 5000, maxSpeed);
    
    amy::ArmComputer::computeMoveStep(oStep1);
    amy::ArmComputer::computeMoveStep(oStep2);
    amy::ArmComputer::computeMoveStep(oStep3);
    amy::ArmComputer::computeMoveStep(oStep4);
    
    LOG4CXX_INFO(logger, "step1: " << oStep1.getDescription());
    LOG4CXX_INFO(logger, "step2: " << oStep2.getDescription());
    LOG4CXX_INFO(logger, "step3: " << oStep3.getDescription());
    LOG4CXX_INFO(logger, "step4: " << oStep4.getDescription());
}
    

void testAmyNetwork2()
{
    LOG4CXX_INFO(logger, "\n\n<<<<<<<<<<<<<<<< TEST AMY NETWORK 2>>>>>>>>>>>>>>");      
    
    // initialize arm network
    amy::ArmNetwork oArmNetwork;
    bool bok = oArmNetwork.init(amy::ArmNetwork::eNETWORK_DB);
    amy::ArmNetwork oArmNetwork2;
    bool bok2 = oArmNetwork2.init(amy::ArmNetwork::eNETWORK_DB);
    
    if (!bok || !bok2)
    {
        LOG4CXX_ERROR(logger, "TEST FAILED");      
        return;
    }
    
    int i=0, iters=12;
    
    while (i<iters) 
    {
        writePos(oArmNetwork, i*10);

        readPos(oArmNetwork2);

        sleep(1);  
        i++;
    }    
    
    LOG4CXX_INFO(logger, "TEST FINISHED");      
}

void writePos(amy::ArmNetwork& oArmNetwork, int value)
{
    amy::ArmData oArmData;
    oArmData.reset();

    oArmData.setSoll1((float)value);
    oArmData.setSoll2(10.0);
    oArmData.setSoll3(10.0);
    oArmData.setSoll4(10.0);
    oArmData.setSoll5(10.0);
//    oArmData.setIst1(21.5);
//    oArmData.setIst2(22.5);
//    oArmData.setIst3(23.5);
//    oArmData.setIst4(24.5);
//    oArmData.setIst5(25.5);    

    // write 
    oArmNetwork.setArmSoll(0, oArmData);
    //oArmNetwork.setArmIst(0, oArmData);
}


void readPos(amy::ArmNetwork& oArmNetwork)
{
    amy::ArmData oArmData;
    oArmData.reset();

    // read     
    oArmNetwork.getArmSoll(0, oArmData);
    //oArmNetwork.getArmIst(0, oArmData);    
    LOG4CXX_INFO(logger, "read:" << oArmData.toString());
}

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <string>
#include <unistd.h> // for sleep() 
#include <cstdlib>  // for getenv
#include <fstream>

#include <log4cxx/logger.h>

#include "amy/main/Tests.h"

#include "amy/main/robots/SupportedRobots.h"
#include "amy/core/robot/Robot.h"
#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/ArmInterface.h"
#include "amy/coms/file/AmyFileServer.h"
#include "amy/coms/file/AmyFilePublisher.h"
#include "amy/coms/file/AmyFileSubscriber.h"
#include "amy/utils/FileReader.h"
#include "amy/utils/FileWriter.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr Tests::logger(Logger::getLogger("amy.main"));    

void Tests::testAmyPublisher()
{
    LOG4CXX_INFO(logger, "> TEST AMY PUBLISHER");      

    // load robot
    SupportedRobots oSupportedRobots;
    Robot oRobot;
    oSupportedRobots.loadRobotVersion(oRobot, SupportedRobots::UR5);
    // create arm bus
    ArmBus oArmBus;
    Arm& oArm = oRobot.getListArms().at(0);        
    oArmBus.init(oArm);
    // create arm interface (connect it to bus)
    ArmInterface oArmInterface;
    oArmInterface.connect(oArmBus);

    // create publisher (connect it to interface)
    AmyFilePublisher oAmyPublisher;
    oAmyPublisher.connect2Arm(oArmInterface);
    // create subscriber
    AmyFileSubscriber oAmyFileSubscriber;
    oAmyFileSubscriber.init();
    ArmData oArmData;

    // change bus
    float angle = 30.0;
    oArmBus.getBusHS().getCO_JOINT_ANGLE().request(angle);
    
    oAmyPublisher.publishArmControl();
    
    oArmData = oAmyFileSubscriber.readArmControl();

    LOG4CXX_INFO(logger, "AmyFileSubscriber > " << oArmData.toString());          
    
    LOG4CXX_INFO(logger, "TEST FINISHED");          
}

void Tests::testAmyServer()
{
    LOG4CXX_INFO(logger, "> TEST AMY SERVER");      

    // load robot
    SupportedRobots oSupportedRobots;
    Robot oRobot;
    oSupportedRobots.loadRobotVersion(oRobot, SupportedRobots::UR5);
    // prepare bus
    ArmBus oArmBus;
    Arm& oArm = oRobot.getListArms().at(0);        
    oArmBus.init(oArm);
    // prepare interface
    ArmInterface oArmInterface;
    oArmInterface.connect(oArmBus);
    // prepare server
    AmyFileServer oAmyFileServer;
    oAmyFileServer.connect2Arm(oArmInterface);
    
    int i=0;    
    while (i<10) 
    {
        sleep(2);  
        if (oAmyFileServer.readCommand())
        {
            if (oAmyFileServer.isValid())
            {
                oAmyFileServer.processCommand();
            }
            else
                LOG4CXX_WARN(logger, "invalid command");                                      
        }
        else
            LOG4CXX_WARN(logger, "no command");                                      

        i++;
    }    
    
    LOG4CXX_INFO(logger, "TEST FINISHED");          
}

void Tests::testFileReader(std::string name)
{
    FileReader oFile;
    
    if (oFile.open(name))        
    {
         LOG4CXX_INFO(logger, "Read start");
         std::string line;
         do 
         {
             line = oFile.readLine();
             LOG4CXX_INFO(logger, line);             
         }
         while (!line.empty());         

         oFile.close();
         LOG4CXX_INFO(logger, "Read end");
    }
    else
     LOG4CXX_ERROR(logger, "Can't open file " << name);
}

void Tests::testFileWriter()
{       
//    char* pVar = getenv("HOME");
//    
//    if (pVar==NULL)
//     LOG4CXX_ERROR(logger, "Test failed: HOME var not found");
//        
//    std::string name(pVar);
//    name = name + "/TESTS/testFile.txt";
    
    FileWriter oFile;
    oFile.setAppendMode(true);
    std::string name = "test.txt";
    testFileReader(name);
    if (oFile.open(name))        
    {
         LOG4CXX_INFO(logger, "write start")                 
        std::string line = " frase de prueba\n";
        oFile.writeFlush(line);
        testFileReader(name);

        //oFile.goTop();
        std::string line2 = " frase de prueba2\n";
        oFile.writeFlush(line2);
        testFileReader(name);

        std::string line3 = " frase de prueba3\n";
        oFile.writeFlush(line3);
        testFileReader(name);
        LOG4CXX_INFO(logger, "write end");
        oFile.close();
    }
    else
     LOG4CXX_ERROR(logger, "Test failed: unable to open file " << name);
}


void Tests::testAmyNetwork2()
{
    LOG4CXX_INFO(logger, "\n\n<<<<<<<<<<<<<<<< TEST AMY NETWORK 2>>>>>>>>>>>>>>");      
    
    // initialize arm network
    ArmNetwork oArmNetwork;
    bool bok = oArmNetwork.init(ArmNetwork::eNETWORK_DB);
    ArmNetwork oArmNetwork2;
    bool bok2 = oArmNetwork2.init(ArmNetwork::eNETWORK_DB);
    
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

void Tests::writePos(ArmNetwork& oArmNetwork, int value)
{
    ArmDataN oArmData;
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


void Tests::readPos(ArmNetwork& oArmNetwork)
{
    ArmDataN oArmData;
    oArmData.reset();

    // read     
    oArmNetwork.getArmSoll(0, oArmData);
    //oArmNetwork.getArmIst(0, oArmData);    
    LOG4CXX_INFO(logger, "read:" << oArmData.toString());
}

}
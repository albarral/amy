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
#include "amy/show/arm/ArmFrontView.h"
#include "amy/show/history/History.h"
#include "amy/show/history/HistoryPlot.h"
#include "amy/show/SharedDisplay.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr Tests::logger(Logger::getLogger("amy.main"));    

void Tests::testAmyPublisher()
{
    LOG4CXX_INFO(logger, "> TEST AMY PUBLISHER");      

    // create publisher 
    AmyFilePublisher oAmyPublisher;
    oAmyPublisher.init();
    // create subscriber
    AmyFileSubscriber oAmyFileSubscriber;
    oAmyFileSubscriber.init();
    
    ArmData oArmData;
    ArmData oArmData2;
    oArmData.setSollHS(69);

    oAmyPublisher.publishArmControl(oArmData);
    
    oArmData2 = oAmyFileSubscriber.readArmControl();

    LOG4CXX_INFO(logger, "AmyFileSubscriber > " << oArmData.toString());          
    
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

void Tests::testArmPlot()
{       
    SharedDisplay oSharedDisplay;
    ArmFrontView oArmFrontView;    

    int w = 200;
    int h = 100;
    oSharedDisplay.initDisplay();
    oArmFrontView.initPlot(200, 200, "prueba");
    oArmFrontView.setRanges(-200, 200, -20, 120);
    
    oArmFrontView.drawArm(10, 20, 0, 90);
    oSharedDisplay.updateDisplayUp2(oArmFrontView.getImage());
    oSharedDisplay.show();
    sleep(4);    
}


void Tests::testHistoryPlot()
{
    SharedDisplay oSharedDisplay;
    HistoryPlot oHistoryPlot;
    
    oSharedDisplay.initDisplay();
    oHistoryPlot.setParams(400, 100);
    oHistoryPlot.configDraw("histplot", 400);
    
    History oHistory;
    for (int i=0; i<20; i++)
    {
        float value = 3.0*i;
        oHistory.addRecord(value);
        usleep(100000); // wait 100 ms
    }
    
    oHistoryPlot.drawHistory(oHistory);    
    oSharedDisplay.updateDisplayMiddle(oHistoryPlot.getImage());
    oSharedDisplay.show();
    sleep(5);    
}

}
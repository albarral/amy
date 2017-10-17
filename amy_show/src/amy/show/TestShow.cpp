/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>

#include "amy/show/TestShow.h"

#include "amy/show/arm/ArmFrontView.h"
#include "amy/show/history/History.h"
#include "amy/show/history/HistoryPlot.h"
#include "amy/show/DiscPlot.h"
#include "amy/show/SharedDisplay.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr TestShow::logger(Logger::getLogger("amy.show"));    

void TestShow::testArmPlot()
{       
    SharedDisplay oSharedDisplay;
    ArmFrontView oArmFrontView;    

    oSharedDisplay.initDisplay();
    oArmFrontView.initPlot(200, 200, "prueba");
    oArmFrontView.setRanges(-200, 200, -20, 120);
    
    oArmFrontView.drawArm(10, 20, 0, 90);
    oSharedDisplay.updateDisplayUp2(oArmFrontView.getImage());
    oSharedDisplay.show();
    sleep(4);    
}


void TestShow::testHistoryPlot()
{
    SharedDisplay oSharedDisplay;
    HistoryPlot oHistoryPlot;
    
    oSharedDisplay.initDisplay();
    oHistoryPlot.setParams(400, 100);
    oHistoryPlot.configDraw("histplot", 400, 200);
    
    History oHistory;
    for (int i=0; i<20; i++)
    {
        float value = 3.0*i;
        oHistory.addRecord(value);
        usleep(100000); // wait 100 ms
    }
    
    oHistoryPlot.drawHistory(oHistory);    
    oSharedDisplay.updateDisplayMid1(oHistoryPlot.getImage());
    oSharedDisplay.show();
    sleep(5);    
}

void TestShow::testDiscPlot()
{
    SharedDisplay oSharedDisplay;
    DiscPlot oDiscPlot;
    
    oSharedDisplay.initDisplay();
    oDiscPlot.initPlot(oSharedDisplay.getDisplayUpW(), oSharedDisplay.getDisplayUpH(), "HS");
        
    oDiscPlot.drawDisc(true);
    oSharedDisplay.updateDisplayUp1(oDiscPlot.getImage());
    oSharedDisplay.show();
    sleep(3);    
    oDiscPlot.drawDisc(false);
    oSharedDisplay.updateDisplayUp1(oDiscPlot.getImage());
    oSharedDisplay.show();
    sleep(3);    
}

}
/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/modules/HistoryPlotter.h"

namespace amy
{
// Constructor 
HistoryPlotter::HistoryPlotter()
{    
    modName = "HistoryPlotter";
    bconnected = false;
    pArmBus = 0;
    pPanBus = 0;
    //pTiltBus = 0;
 }

HistoryPlotter::~HistoryPlotter()
{
    // hide windows
    oPanHistoryPlot.hide();        
}

void HistoryPlotter::connect(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;
    pPanBus = &pArmBus->getPanBus();
    //pTiltBus = &pArmBus->getTiltBus(); 
    bconnected = true;
}

void HistoryPlotter::first()
{
    int timeSpan = 10000;    // 10s history shown
    int signalRange = 150;  // speed range
    // plot (400 pixels wide)
    oPanHistoryPlot.setParams(timeSpan, signalRange);
    oPanHistoryPlot.configDraw("Speeds", 400);
    oPanHistory2D.setTimeSpan(timeSpan);
}
                    
// drives the axis towards the target position
void HistoryPlotter::loop()
{
    senseBus();
    // draw pan speed history
    oPanHistoryPlot.draw2DHistory(oPanHistory2D);
    oPanHistoryPlot.show();    
}

void HistoryPlotter::senseBus()
{
    float panSOSpeed = pPanBus->getSO_AXIS_SPEED().getValue();
    float panCOSpeed = pPanBus->getCO_AXIS_SPEED().getValue();
    oPanHistory2D.addRecord(panSOSpeed, panCOSpeed);
}


}
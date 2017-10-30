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
    pPanBus = 0;
    pTiltBus = 0;
    pSharedDisplay = 0;
 }

HistoryPlotter::~HistoryPlotter()
{
}

void HistoryPlotter::connect(ArmBus& oArmBus)
{
    pPanBus = &oArmBus.getPanBus();
    pTiltBus = &oArmBus.getTiltBus(); 
    bconnected = true;
}

void HistoryPlotter::shareDisplay(tivy::SharedDisplay& oSharedDisplay)
{
    pSharedDisplay = &oSharedDisplay;    
}

void HistoryPlotter::first()
{
    int timeSpan = 10000;    // 10s history shown
    int signalRange = 150;  // speed range
    // plot pan
    oPanHistoryPlot.setParams(timeSpan, signalRange);
    oPanHistoryPlot.configDraw("Pan speed", pSharedDisplay->getDisplayMidW(), pSharedDisplay->getDisplayMidH());
    oPanHistory2D.setTimeSpan(timeSpan);
    // plot tilt 
    oTiltHistoryPlot.setParams(timeSpan, signalRange);
    oTiltHistoryPlot.configDraw("Tilt speed", pSharedDisplay->getDisplayMidW(), pSharedDisplay->getDisplayMidH());
    oTiltHistory2D.setTimeSpan(timeSpan);
}
                    
// drives the axis towards the target position
void HistoryPlotter::loop()
{
    senseBus();
    // draw pan speed history
    oPanHistoryPlot.draw2DHistory(oPanHistory2D);
    // draw tilt speed history
    oTiltHistoryPlot.draw2DHistory(oTiltHistory2D);

    // show window
    if (pSharedDisplay != 0)
    {    
        // put the pan speed in the display (middle 1 window)
        pSharedDisplay->updateDisplayMid1(oPanHistoryPlot.getImage());
        // put the tilt speed in the display (middle 2 window)
        pSharedDisplay->updateDisplayMid2(oTiltHistoryPlot.getImage());
    }
}

void HistoryPlotter::senseBus()
{
    // update pan speed history
    float panSOSpeed = pPanBus->getSO_AXIS_SPEED().getValue();
    float panCOSpeed = pPanBus->getCO_AXIS_SPEED().getValue();
    oPanHistory2D.addRecord(panSOSpeed, panCOSpeed);
    // update tilt speed history
    float tiltSOSpeed = pTiltBus->getSO_AXIS_SPEED().getValue();
    float tiltCOSpeed = pTiltBus->getCO_AXIS_SPEED().getValue();
    oTiltHistory2D.addRecord(tiltSOSpeed, tiltCOSpeed);
}


}
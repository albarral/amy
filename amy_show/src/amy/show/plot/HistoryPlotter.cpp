/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/plot/HistoryPlotter.h"

namespace amy
{
// Constructor 
HistoryPlotter::HistoryPlotter()
{    
 }

//HistoryPlotter::~HistoryPlotter()
//{
//}

void HistoryPlotter::init(tivy::SharedDisplay& oSharedDisplay)
{
    int timeSpan = 10000;    // 10s history shown
    int signalRange = 150;  // speed range
    // plot pan
    oPanHistoryPlot.setParams(timeSpan, signalRange);
    oPanHistoryPlot.configDraw("Pan speed", oSharedDisplay.getDisplayMidW(), oSharedDisplay.getDisplayMidH());
    oPanHistory2D.setTimeSpan(timeSpan);
    // plot tilt 
    oTiltHistoryPlot.setParams(timeSpan, signalRange);
    oTiltHistoryPlot.configDraw("Tilt speed", oSharedDisplay.getDisplayMidW(), oSharedDisplay.getDisplayMidH());
    oTiltHistory2D.setTimeSpan(timeSpan);
}
                    
// drives the axis towards the target position
void HistoryPlotter::draw(tivy::SharedDisplay& oSharedDisplay, ShowData* pShowData)
{
    DataBlockAxes& oDataBlockAxes = pShowData->getDataBlockAxes();
    
    // update pan speed history
    float panSOSpeed = oDataBlockAxes.getPanSpeed();
    float panCOSpeed = 0; //pPanBus->getCO_AXIS_SPEED().getValue();
    oPanHistory2D.addRecord(panSOSpeed, panCOSpeed);
    // update tilt speed history
    float tiltSOSpeed = oDataBlockAxes.getTiltSpeed();
    float tiltCOSpeed = 0; //pTiltBus->getCO_AXIS_SPEED().getValue();
    oTiltHistory2D.addRecord(tiltSOSpeed, tiltCOSpeed);

    // draw pan speed history
    oPanHistoryPlot.draw2DHistory(oPanHistory2D);
    // draw tilt speed history
    oTiltHistoryPlot.draw2DHistory(oTiltHistory2D);

    // show window
    // put the pan speed in the display (middle 1 window)
    oSharedDisplay.updateDisplayMid1(oPanHistoryPlot.getImage());
    // put the tilt speed in the display (middle 2 window)
    oSharedDisplay.updateDisplayMid2(oTiltHistoryPlot.getImage());
}

}
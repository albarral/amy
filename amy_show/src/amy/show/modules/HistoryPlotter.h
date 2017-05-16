#ifndef __AMY_SHOW_HISTORYPLOTTER_H
#define __AMY_SHOW_HISTORYPLOTTER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <amy/control/module3.h>
#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/bus/AxisBus.h"
#include "amy/show/history/HistoryPlot.h"
#include "amy/show/history/History2D.h"
#include "amy/show/SharedDisplay.h"

namespace amy
{
// Module used to plot the evolution of arm signals (for debugging purpose).
// It gets the info from the arm bus.
class HistoryPlotter : public Module3
{
private:
    // bus
    bool bconnected;        // connected to bus
    AxisBus* pPanBus;      // access to pan bus 
    AxisBus* pTiltBus;      // access to tilt bus
    // logic
    History2D oPanHistory2D;        // pan speed history
    HistoryPlot oPanHistoryPlot;    // plotting of pan speed
    History2D oTiltHistory2D;       // tilt speed history
    HistoryPlot oTiltHistoryPlot;    // plotting of tilt speed
    SharedDisplay* pSharedDisplay;  // access to the shared display 

public:
    HistoryPlotter();
    ~HistoryPlotter();

    // bus connection 
    void connect(ArmBus& oArmBus);
    bool isConnected() {return bconnected;};
    void shareDisplay(SharedDisplay& oSharedDisplay);
    
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        // read bus data   
        virtual void senseBus();
};
}		
#endif

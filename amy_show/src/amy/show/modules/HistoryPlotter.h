#ifndef __AMY_SHOW_HISTORYPLOTTER_H
#define __AMY_SHOW_HISTORYPLOTTER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <tuly/control/module3.h>
#include "amy/core/bus/ArmBus.h"
#include "amy/core/bus/AxisBus.h"
#include "tivy/plot/HistoryPlot.h"
#include "tivy/history/History2D.h"
#include "tivy/SharedDisplay.h"

namespace amy
{
// Module used to plot the evolution of arm signals (for debugging purpose).
// It gets the info from the arm bus.
class HistoryPlotter : public tuly::Module3
{
private:
    // bus
    bool bconnected;        // connected to bus
    AxisBus* pPanBus;      // access to pan bus 
    AxisBus* pTiltBus;      // access to tilt bus
    // logic
    tivy::History2D oPanHistory2D;        // pan speed history
    tivy::HistoryPlot oPanHistoryPlot;    // plotting of pan speed
    tivy::History2D oTiltHistory2D;       // tilt speed history
    tivy::HistoryPlot oTiltHistoryPlot;    // plotting of tilt speed
    tivy::SharedDisplay* pSharedDisplay;  // access to the shared display 

public:
    HistoryPlotter();
    ~HistoryPlotter();

    // bus connection 
    void connect(ArmBus& oArmBus);
    bool isConnected() {return bconnected;};
    void shareDisplay(tivy::SharedDisplay& oSharedDisplay);
    
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

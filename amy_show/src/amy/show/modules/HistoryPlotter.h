#ifndef __AMY_SHOW_HISTORYPLOTTER_H
#define __AMY_SHOW_HISTORYPLOTTER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <amy/utils/module3.h>
#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/bus/AxisBus.h"
#include "amy/show/history/HistoryPlot.h"
#include "amy/show/history/History2D.h"

namespace amy
{
// Module used to plot the evolution of arm signals (for debugging purpose).
// It gets the info from the arm bus.
class HistoryPlotter : public Module3
{
private:
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pArmBus;     // access to arm's bus
    AxisBus* pPanBus;      // access to pan bus 
    //AxisBus* pTiltBus;      // access to tilt bus
    // logic
    History2D oPanHistory2D;
    HistoryPlot oPanHistoryPlot;    // plotting of pan speed

public:
    HistoryPlotter();
    ~HistoryPlotter();

    // bus connection 
    void connect(ArmBus& oArmBus);
    bool isConnected() {return bconnected;};
    
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

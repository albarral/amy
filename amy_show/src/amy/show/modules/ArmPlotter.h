#ifndef __AMY_SHOW_ARMPLOTTER_H
#define __AMY_SHOW_ARMPLOTTER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <amy/utils/module3.h>
#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/show/arm/ArmFrontView.h"
#include "amy/show/arm/ArmSideView.h"
#include "amy/show/DiscPlot.h"
#include "amy/show/SharedDisplay.h"

namespace amy
{
// Module used to plot an arm's position (for debugging purpose).
// It gets the info from the arm bus.
class ArmPlotter : public Module3
{
private:
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pArmBus;     // access to arm's bus
    JointBus* pHSBus;     // access to arm's HS joint
    JointBus* pVSBus;     // access to arm's VS joint
    JointBus* pELBus;     // access to arm's ELB joint
    // data
    float pan;
    float tilt;
    float radius;
    float angleVS;
    float angleELB;
    int limitHS;
    int limitVS;
    int limitELB;
    // display
    SharedDisplay* pSharedDisplay;      // pointer to shared display (used to avoid X11 problems with different threads)
    ArmFrontView oArmFrontView;    // plotting of frontal arm view 
    ArmSideView oArmSideView;     // plotting of side arm view  
    DiscPlot oHSDiscPlot;               // plotting of HS limit reached
    DiscPlot oHSDiscPlot2;             // plotting of VS limit reached 
    DiscPlot oHSDiscPlot3;             // plotting of ELB limit reached
//    DiscPlot oHSDiscPlot4;             // plotting of HWRI limit reached 
//    DiscPlot oHSDiscPlot5;             // plotting of VWRI limit reached  

public:
    ArmPlotter();
    ~ArmPlotter();

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

#ifndef __AMY_SHOW_ARMPLOTTER_H
#define __AMY_SHOW_ARMPLOTTER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <tuly/control/module3.h>
#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/show/arm/ArmFrontView.h"
#include "amy/show/arm/ArmSideView.h"
#include "tivy/plot/DiscPlot.h"
#include "tivy/SharedDisplay.h"

namespace amy
{
// Module used to plot an arm's position (for debugging purpose).
// It gets the info from the arm bus.
class ArmPlotter : public tuly::Module3
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
    int stateHS;    // HS driver state
    int stateVS;    // VS driver state
    int stateELB;   // ELB driver state
    // display
    tivy::SharedDisplay* pSharedDisplay;      // pointer to shared display (used to avoid X11 problems with different threads)
    ArmFrontView oArmFrontView;    // plotting of frontal arm view 
    ArmSideView oArmSideView;     // plotting of side arm view  
    // disk plots
    tivy::DiscPlot oDiscPlot1;  
    tivy::DiscPlot oDiscPlot2;  
    tivy::DiscPlot oDiscPlot3;  

public:
    ArmPlotter();
    ~ArmPlotter();

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
        
        // translate state of joint driver module to DiscPlot color
        int driverState2DiscColor(int driveState);
};
}		
#endif

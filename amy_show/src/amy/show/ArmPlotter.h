#ifndef __AMY_SHOW_ARMPLOTTER_H
#define __AMY_SHOW_ARMPLOTTER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <amy/utils/module3.h>
#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/bus/JointBus.h"
#include "amy/show/ArmFrontView.h"
//#include "amy/show/ArmSideView.h"

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
    JointBus* pVSBus;     // access to arm's VS joint
    float pan;
    float tilt;
    //float radius;
    float vsAngle;
    ArmFrontView oArmFrontView;
    //ArmSideView oArmFrontView2;

public:
    ArmPlotter();
    ~ArmPlotter();

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

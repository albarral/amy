#ifndef __AMY_SHOW_ARMPLOTTER_H
#define __AMY_SHOW_ARMPLOTTER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/ShowData.h"
#include "amy/show/arm/ArmFrontView.h"
#include "amy/show/arm/ArmSideView.h"
#include "tivy/SharedDisplay.h"
#include "tivy/plot/DiscPlot.h"


namespace amy
{
// Class used to plot an arm's position (for debugging purpose).
class ArmPlotter
{
private:
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
    ArmFrontView oArmFrontView;    // plotting of frontal arm view 
    ArmSideView oArmSideView;     // plotting of side arm view  
    // disk plots
    tivy::DiscPlot oDiscPlot1;  
    tivy::DiscPlot oDiscPlot2;  
    tivy::DiscPlot oDiscPlot3;  

public:
    ArmPlotter();
    //~ArmPlotter();
        
    // initialize plot
    void init(tivy::SharedDisplay& oSharedDisplay);
    // draw plot
    void draw(tivy::SharedDisplay& oSharedDisplay, ShowData* pShowData);
    
private:
        // translate state of joint driver module to DiscPlot color
        int driverState2DiscColor(int driveState);
};
}		
#endif

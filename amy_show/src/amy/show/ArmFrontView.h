#ifndef __AMY_SHOW_ARMFRONTVIEW_H
#define __AMY_SHOW_ARMFRONTVIEW_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/ArmPlot.h"

namespace amy 
{
// This class plots a frontal view of the arm.
class ArmFrontView : public ArmPlot
{
public:
    ArmFrontView();
    
    // configure plot (defines window size and name)
    virtual void configDraw(std::string name, int maxSide);
    
    // draws two points (elbow and hand) showing the arm's 2D position
    void drawArm(int pan, int tilt, int radius, int vsAngle);
};
}    
#endif

#ifndef __AMY_SHOW_ARMFRONTVIEW_H
#define __AMY_SHOW_ARMFRONTVIEW_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/Plot.h"

namespace amy 
{
// This class plots in a window an arm's 2D position from a frontal view.
class ArmFrontView : public Plot
{
public:
    ArmFrontView();
    
    // draws two points (elbow and hand) showing the arm's 2D position
    void drawArmPosition(int pan, int tilt, int radius, int vsAngle);
};
}    
#endif

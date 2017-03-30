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
private:    
    static const float KPI_DIV_180;
    
public:
    ArmFrontView();
    
    // configure plot (defines window size and name)
    virtual void configDraw(std::string name, int maxSide);
    
    // draws two segments (humerus and radius) showing the arm's 2D side position
    void drawArm(float vs, float pan, float tilt, float radius);
};
}    
#endif

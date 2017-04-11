#ifndef __AMY_SHOW_ARMSIDEVIEW_H
#define __AMY_SHOW_ARMSIDEVIEW_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/arm/ArmPlot.h"

namespace amy 
{
// This class plots in a side view of the arm.
// It represents the vertical plane positioned over the arm's pan.
class ArmSideView : public ArmPlot
{
private:    
    static const float KPI_DIV_180;
    
public:
    ArmSideView();
    
    // configure plot (defines window size and name)
    virtual void configDraw(std::string name, int maxSide);

    // draws two segments (humerus and radius) showing the arm's 2D side position
    void drawArm(float vs, float elbow);
};
}    
#endif

#ifndef __AMY_SHOW_ARMPLOT_H
#define __AMY_SHOW_ARMPLOT_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/Plot.h"

namespace amy 
{
// This class plots an arm's 2D position in a window.
class ArmPlot : public Plot
{
private:    
    int pan0;   // max negative pan value (represented)
    int pan1;   // max positive pan value (represented)
    int tilt0;    // bottom represented tilt  
    int tilt1;    // top represented tilt  

public:
    ArmPlot();

    void setMaxLimits(int panL, int panR, int tiltBottom, int tiltTop);
    
    // draw a point showing the arm's 2D position
    void drawArmPosition(int pan, int tilt, int radius);
};
}    
#endif

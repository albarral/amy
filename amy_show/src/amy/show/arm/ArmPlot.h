#ifndef __AMY_SHOW_ARMPLOT_H
#define __AMY_SHOW_ARMPLOT_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "opencv2/core/core.hpp"    // for cv::Scalar

#include "amy/show/Plot.h"

namespace amy 
{
// Base class used to plot the arm position in a 2D image.
// Derived from Plot
class ArmPlot : public Plot
{
protected:    
    cv::Scalar handColor;
    cv::Scalar elbowColor;
    // params
    int lenHum; // humerus length (cm)
    int lenRad; // radius length (cm)
    // logic
    int maxLen;   // maximum represented length (cm)

public:
    ArmPlot();
     //~ArmPlot();

    // sets arm sizes (humerus len, radius len)
    void setArmSize(int lenH, int lenR);
    // configure plot (defines window size and name)
    virtual void configDraw(std::string name, int maxSide) = 0;
    
protected:
    // draw elbow and hand segments (ignore out of bound points)    
    void drawElbowAndHand(int xElbow, int yElbow, int xHand, int yHand);
};
}    
#endif

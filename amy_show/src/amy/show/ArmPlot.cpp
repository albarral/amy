/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/ArmPlot.h"

namespace amy 
{
ArmPlot::ArmPlot()
{
    pan0 = -100;
    pan1 = 100;
    tilt0 = -10;
    tilt1 = 150;
}

void ArmPlot::setMaxLimits(int panL, int panR, int tiltBottom, int tiltTop)
{
    pan0 = panL; 
    pan1 = panR;
    tilt0 = tiltBottom;
    tilt1 = tiltTop;
}
    
void ArmPlot::drawArmPosition(int pan, int tilt, int radius)
{  
    // prepare image
    image = cv::Scalar(0,0,0);
    drawAxes();

    cv::Scalar color = cv::Scalar(255, 255, 255);  // white
    
    int x = yaxis + pan;
    // draw upside-down
    int y = H - xaxis - tilt;
    // ignore points that fall out of plot
    if (y>=0 && y<H && x>=0 && x<W)
    {
        cv::circle(image, cv::Point(x, y), 3, color);           
    }
}
}
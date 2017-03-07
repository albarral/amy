/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/ArmFrontView.h"

namespace amy 
{
ArmFrontView::ArmFrontView()
{
}
    
// draws two points (elbow and hand) showing the arm's 2D position
void ArmFrontView::drawArmPosition(int pan, int tilt, int radius, int vsAngle)
{  
    // prepare image
    image = cv::Scalar(0,0,0);
    drawAxes();

    cv::Scalar handColor = cv::Scalar(0, 255, 255);  // yellow
    cv::Scalar elbowColor = cv::Scalar(255, 255, 255);  // white
    
    // hand point represents (pan, tilt)
    // elbow point represents (pan, vsAngle)    
    int x = pan;
    int yHand = tilt;
    int yElbow = vsAngle;
    
    // draw elbow point (ignore out of bound points)
    if (checkRangeLimits(x, yElbow))
    {
        // obtain elbow point in plotted view
        cv::Point elbowPoint = getPoint2Plot(x, yElbow);    
        cv::circle(image, elbowPoint, 5, elbowColor, -1);           
    }
    // draw hand point (ignore out of bound points)
    if (checkRangeLimits(x, yHand))
    {
        // obtain hand point in plotted view
        cv::Point handPoint = getPoint2Plot(x, yHand);    
        cv::circle(image, handPoint, 5, handColor, -1);           
    }
}
}
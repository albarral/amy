/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/arm/ArmPlot.h"

namespace amy 
{
ArmPlot::ArmPlot()
{
    handColor = cv::Scalar(0, 255, 255);  // yellow
    elbowColor = cv::Scalar(255, 255, 255);  // white        
    
    // set default values (20 + 20 arm, window side 200)
    lenHum = 20;
    lenRad = 20;
    maxLen = lenHum + lenRad + 5;
}

    
void ArmPlot::setArmSize(int lenH, int lenR)
{    
    // assure valid values
    if ((lenH > 0) && (lenR > 0))
    {
        lenHum = lenH;
        lenRad = lenR;        
        maxLen = lenHum + lenRad + 5;
    }
}

void ArmPlot::drawElbowAndHand(int xElbow, int yElbow, int xHand, int yHand)
{
    // the arm base will be at origin 
    cv::Point origin = cv::Point(x0, y0);
    cv::Point elbowPoint, handPoint;
    bool belbowVisible = false; // indicates elbow is visible in image
    
    // draw elbow point and line base-elbow (ignore out of bound points)
    if (checkRangeLimits(xElbow, yElbow))
    {
        // obtain elbow point in plotted view
        elbowPoint = getPoint2Plot(xElbow, yElbow);    
        cv::circle(image, elbowPoint, 5, elbowColor, -1);                   
        cv::line(image, origin, elbowPoint, elbowColor);   
        belbowVisible = true;
    }
    // draw hand point and line elbow-hand (ignore out of bound points)
    if (checkRangeLimits(xHand, yHand))
    {
        // obtain hand point in plotted view
        handPoint = getPoint2Plot(xHand, yHand);    
        cv::circle(image, handPoint, 5, handColor, -1);                   
        // draw elbow-hand line only if elbow is visible
        if (belbowVisible)
            cv::line(image, elbowPoint, handPoint, handColor);           
    }
}

}
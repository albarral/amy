/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/show/ArmSideView.h"

namespace amy 
{
const float ArmSideView::KPI_DIV_180 = 0.0174;    

ArmSideView::ArmSideView()
{
}

void ArmSideView::configDraw(std::string name, int maxSide)
{
    // create a rectangular window of maxSide/2 x maxSide ...
    // able to represent the arm in 3 directions (up, down and right)
    initPlot(maxSide/2, maxSide, name);   
    setRanges(0, maxLen, -maxLen, maxLen);
}

// draws two segments (humerus and radius) showing the arm's 2D side position
void ArmSideView::drawArm(float vs, float elbow, int lenHum, int lenRad)
{  
    // prepare image
    image = cv::Scalar(0,0,0);
    drawAxes();

    // vertical plane positioned on the arm's pan angle
    // vs and elbow angles don't need projection

    float radiansVS = vs * KPI_DIV_180;
    // gamma = vs + elbow       (hand angle relative to horizontal at elbow)
    float radiansHandFromElbow = (vs + elbow) * KPI_DIV_180;
    
    // elbow point, depends on VS and humerus length 
    int xElbow = lenHum*cos(radiansVS);
    int yElbow = lenHum*sin(radiansVS);
    
    // hand point, depends on elbow point, ELB and radius length 
    int xHand = xElbow + lenRad*cos(radiansHandFromElbow);
    int yHand = yElbow + lenRad*sin(radiansHandFromElbow);

    // the arm base will be shown at axis origin 
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
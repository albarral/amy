/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/show/arm/ArmSideView.h"

namespace amy 
{
const float ArmSideView::KPI_DIV_180 = 0.0174;    

ArmSideView::ArmSideView()
{
}

void ArmSideView::configDraw(std::string name, int w, int h)
{
    // create an image of the specified size
    // able to represent the arm in 3 directions (up, down and right)
    // with isotropic scaling (same scale in all directions)
    setIsotropic(true);
    initPlot(w, h, name);   
    // only positive x ranges
    setRanges(0, maxLen, -maxLen, maxLen);
}

// draws two segments (humerus and radius) showing the arm's 2D lateral projection
// the vertical plane over the pan angle is represented here, so no projections are needed
// elbow = (lHum*cos(vs), lHum*sin(vs))
// hand  = elbow + (lRad*cos(elb2hand), lRad*sin(elb2hand))
// elb2hand = vs + elb      ...  elbow to hand relative angle (taken from the elbow's horizontal plane)
void ArmSideView::drawArm(float vs, float elbow)
{  
    // prepare image
    image = cv::Scalar(0,0,0);
    drawAxes();

    float vsRadians = vs * KPI_DIV_180;
    float elb2handRadians = (vs + elbow) * KPI_DIV_180;
    
    // compute positions of elbow & hand from a lateral view
    int xElbow = lenHum*cos(vsRadians);
    int yElbow = lenHum*sin(vsRadians);
    int xHand = xElbow + lenRad*cos(elb2handRadians);
    int yHand = yElbow + lenRad*sin(elb2handRadians);

    // draws both points and segments
    drawElbowAndHand(xElbow, yElbow, xHand, yHand);
}

}
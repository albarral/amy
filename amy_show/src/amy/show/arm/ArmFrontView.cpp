/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/show/arm/ArmFrontView.h"

namespace amy 
{
const float ArmFrontView::KPI_DIV_180 = 0.0174;    
    
ArmFrontView::ArmFrontView()
{
}

void ArmFrontView::configDraw(std::string name, int w, int h)
{
    // create an image of the specified size
    // able to represent arm in all directions (up, down, left and right)
    // with isotropic scaling (same scale in all directions)
    setIsotropic(true);
    initPlot(w, h, name);   
    setRanges(-maxLen, maxLen, -maxLen, maxLen);
}

// draws two segments (humerus and radius) showing the arm's 2D frontal projection
// elbow = (l1*sin(pan), lHum*sin(vs))
// hand  = (l2*sin(pan), lHand*sin(tilt))
// l1 = lHum*cos(vs)      ... humerus projection on horizontal plane
// l2 = radius*cos(tilt)    ... arm projection on horizontal plane
void ArmFrontView::drawArm(float vs, float pan, float tilt, float radius)
{  
    // prepare image
    image = cv::Scalar(0,0,0);
    drawAxes();
    
    float vsRadians = vs * KPI_DIV_180;
    float tiltRadians = tilt * KPI_DIV_180;
    float sinusPan = sin(pan * KPI_DIV_180);
         
    // compute positions of elbow & hand from a frontal view
    int xElbow = lenHum * cos(vsRadians) * sinusPan;    
    int yElbow = lenHum * sin(vsRadians);
    int xHand = radius * cos(tiltRadians) * sinusPan;    
    int yHand = radius * sin(tiltRadians);
    
    // draws both points and segments
    drawElbowAndHand(xElbow, yElbow, xHand, yHand);
}

}
/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/DiscPlot.h"

namespace amy 
{
DiscPlot::DiscPlot()
{
    colorGood = cv::Scalar(0, 255, 0);       // green
    colorBad = cv::Scalar(0, 0, 255);         // red     
    colorText = cv::Scalar(255, 255, 255);  // white
    fontFace = cv::FONT_HERSHEY_SIMPLEX;
    fontScale = 0.3;
    thickness = 1;
}

void DiscPlot::initPlot(int w, int h, std::string name)
{
     W=w; 
     H=h; 
     plotName = name;
     
     // disc will be located in center of image
     center.x = 0.5*w;
     center.y = 0.5*h;
     // radius will be 20% of the smaller side
     int min = (w < h ? w : h);
     radius = 0.2*min;
     
     // text will be located upper in the image
     textOrigin.x = 0.4*w;
     textOrigin.y = 0.2*h;     
     
     // create clean image
     image = cv::Mat::zeros(H, W, CV_8UC3);           
}

void DiscPlot::drawDisc(bool bgood)
{
    // prepare image
    image = cv::Scalar(0,0,0);

    // the arm base will be at origin 
    cv::putText(image, plotName, textOrigin, fontFace, fontScale, colorText, thickness, 8);

    // draw disc indicating good status
    if (bgood)
        cv::circle(image, center, radius, colorGood, -1);                   
    // draw disc indicating bad status
    else
        cv::circle(image, center, radius, colorBad, -1);                   
}

}
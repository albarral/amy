/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/highgui/highgui.hpp>  // for named window

#include "amy/show/Plot.h"

namespace amy 
{
Plot::Plot()
{
    W = H = 100;
    xaxis = yaxis = 50;
}

void Plot::setPlot(int w, int h, int posXaxis, int posYaxis, std::string name)
{
     W=w; 
     H=h; 
     xaxis=posXaxis; 
     yaxis=posYaxis;
     plotName = name;
     // create clean RGB image        
     image = cv::Mat::zeros(H, W, CV_8UC3);      
     
     cv::namedWindow(plotName);         
}
    
void Plot::show()
{  
    // show plot
    cv::imshow(plotName, image);
    cv::waitKey(100);    
}

void Plot::hide()
{
    cv::destroyWindow(plotName);
    //cv::destroyAllWindows();    
}

void Plot::drawAxes()
{
    cv::Scalar colorAxis = cv::Scalar(0, 0, 255);  // red
    // set axes limits
    cv::Point x0 = cv::Point(0, H-xaxis);
    cv::Point x1 = cv::Point(W-1, H-xaxis);
    cv::Point y0 = cv::Point(yaxis, H-1);
    cv::Point y1 = cv::Point(yaxis, 0);   
    // draw xaxis
    cv::line(image, x0, x1, colorAxis);
    // draw yaxis
    cv::line(image, y0, y1, colorAxis);   
}

}
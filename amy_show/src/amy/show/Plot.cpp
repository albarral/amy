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
    margin = 10; // 10 pixels margin
    setPlotSize(120, 120, "default");
    setRanges(-50, 50, -50, 50);
}

void Plot::setPlotSize(int w, int h, std::string name)
{
     W=w; 
     H=h; 
     plotName = name;     
     // update conversion factors and origin position
     computeFactorsAndOrigin();

     // create clean image and window      
     image = cv::Mat::zeros(H, W, CV_8UC3);           
     cv::namedWindow(plotName);         
}
    
// set plotted ranges 
void Plot::setRanges(int xmin, int xmax, int ymin, int ymax)
{
    // skip if null ranges specified
    if ((xmin == xmax) || (ymin == ymax))
        return;
    
    this->xmin = xmin; 
    this->xmax = xmax;
    this->ymin = ymin;
    this->ymax = ymax;
    
    // update conversion factors and origin position
    computeFactorsAndOrigin();
}

void Plot::computeFactorsAndOrigin()
{
    // compute conversion factors
    xfactor = (float)(xmax - xmin) / (W - 2*margin);
    yfactor = (float)(ymax - ymin) / (H - 2*margin);
    // compute origin position in image
    x0 = margin + abs(xmin)/xfactor;
    y0 = margin + abs(ymin)/yfactor;    
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
    cv::Point x1 = cv::Point(margin, H-y0);
    cv::Point x2 = cv::Point(W-margin, H-y0);
    cv::Point y1 = cv::Point(x0, margin);
    cv::Point y2 = cv::Point(x0, H-margin);   
    // draw xaxis
    cv::line(image, x1, x2, colorAxis);
    // draw yaxis
    cv::line(image, y1, y2, colorAxis);   
}
    
// checks if given physical point (x,y) is inside the represented ranges
bool Plot::checkRangeLimits(float x, float y)
{
    return (x>=xmin && x<=xmax && y>=ymin && y<=ymax);
}

// transform the specified physical point (x,y) into its representing plotted point in image
cv::Point Plot::getPoint2Plot(float x, float y)
{
    return cv::Point(x0 + x/xfactor, H - (y0 + y/yfactor));  // draw upside-down
}

}
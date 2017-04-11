/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/highgui/highgui.hpp>  // for named window

#include "amy/show/Plot.h"

namespace amy 
{
Plot::Plot()
{
    margin = 10; // 10 pixels margin
    xscale = yscale = 1.0;
    bisotropic = false;
}

void Plot::initPlot(int w, int h, std::string name)
{
     W=w; 
     H=h; 
     // update scale and origin position
     updateScale();

     // create clean image and window      
     plotName = name;
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
    
     // update scale and origin position
    updateScale();
}

void Plot::setIsotropic(bool bvalue)
{
    bisotropic = bvalue;
}

void Plot::updateScale()
{
    // compute drawing scales
    if (xmax - xmin > 0)
        xscale = (float)(W - 2*margin) / (xmax - xmin);
    if (ymax - ymin > 0)
        yscale = (float)(H - 2*margin) / (ymax - ymin);
    
    // compute origin position in image
    if (xscale > 0)
        x0 = margin + abs(xmin)*xscale;
    if (yscale > 0)
        y0 = margin + abs(ymin)*yscale;    

    // if isotropy required, use the same scale factor for both axes (the smaller)
    if (bisotropic)
    {
        if (xscale > yscale) 
            xscale = yscale;
        else
            yscale = xscale;
    }
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
    return cv::Point(x0 + x*xscale, H - (y0 + y*yscale));  // draw upside-down
}

}
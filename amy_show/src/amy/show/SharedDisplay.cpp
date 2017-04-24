/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/highgui/highgui.hpp>  // for named window

#include "amy/show/SharedDisplay.h"

namespace amy 
{
SharedDisplay::SharedDisplay()
{
    windowName = "amy display";
    up_w = 200;
    up_h = 200;
    mid_w = bot_w = 400;
    mid_h = bot_h = 100;
}
    
SharedDisplay::~SharedDisplay()
{    
    // hide window
    cv::destroyWindow(windowName);
}

// create display image and sub-windows
void SharedDisplay::initDisplay()
{
    std::lock_guard<std::mutex> locker(mutex);

    // compute display width (max of windows widths)
    int W = 2*up_w;
    if (W < mid_w)
        W = mid_w;
    if (W < bot_w)
        W = bot_w;    
    // compute display height (sum of windows heights)
    int H = up_h + mid_h + bot_h;
    
    // create the display image (clean)    
    image = cv::Mat::zeros(H, W, CV_8UC3);           
     
     // create the sub-windows
    window_up1 = cv::Rect(0, 0, up_w, up_h);
    window_up2 = cv::Rect(up_w, 0, up_w, up_h);
    window_mid = cv::Rect(0, up_h, mid_w, mid_h);
    window_bot = cv::Rect(0, up_h + mid_h, bot_w, bot_h);
    image_up1 = image(window_up1);
    image_up2 = image(window_up2);
    image_mid = image(window_mid);
    image_bot = image(window_bot);

    // create display window
    cv::namedWindow(windowName);              
}

void SharedDisplay::updateDisplayUp1(cv::Mat& img)
{  
    std::lock_guard<std::mutex> locker(mutex);
    
    img.copyTo(image_up1);
}

void SharedDisplay::updateDisplayUp2(cv::Mat& img)
{  
    std::lock_guard<std::mutex> locker(mutex);
    
    img.copyTo(image_up2);
}

void SharedDisplay::updateDisplayMiddle(cv::Mat& img)
{  
    std::lock_guard<std::mutex> locker(mutex);
    
    img.copyTo(image_mid);
}

void SharedDisplay::updateDisplayBottom(cv::Mat& img)
{  
    std::lock_guard<std::mutex> locker(mutex);
    
    img.copyTo(image_bot);
}

void SharedDisplay::show()
{
    std::lock_guard<std::mutex> locker(mutex);
  
    // show plot
    cv::imshow(windowName, image);
    cv::waitKey(100);    
}

}
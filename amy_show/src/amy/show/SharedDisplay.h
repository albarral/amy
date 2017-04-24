#ifndef __AMY_SHOW_SHARED_DISPLAY_H
#define __AMY_SHOW_SHARED_DISPLAY_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include "opencv2/core/core.hpp"    // for mat

namespace amy 
{
// This class represents the amy display, which can hold different plots thanks to its division in sub-windows.
// The drawing and showing of the display is designed to be thread safe, to allow concurrent plotters and displayer. 
// The display is composed by 2 upper windows, one mid window, and one bottom window.    
class SharedDisplay
{
private:    
        std::mutex mutex;
        // display 
        cv::Mat image;
        std::string windowName;        
        // window sizes
        int up_w;
        int up_h;
        int mid_w;
        int mid_h;
        int bot_w;
        int bot_h;
        // display windows
        cv::Rect window_up1;
        cv::Rect window_up2;
        cv::Rect window_mid;
        cv::Rect window_bot;
        // display ROIs
        cv::Mat image_up1;
        cv::Mat image_up2;
        cv::Mat image_mid;
        cv::Mat image_bot;                        

public:
    SharedDisplay();       
    ~SharedDisplay();
    
    void initDisplay();
    // update display sub-windows
    void updateDisplayUp1(cv::Mat& img);
    void updateDisplayUp2(cv::Mat& img);
    void updateDisplayMiddle(cv::Mat& img);
    void updateDisplayBottom(cv::Mat& img);
    // show display on screen
    void show();
};
}    
#endif

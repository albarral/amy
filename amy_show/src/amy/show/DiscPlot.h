#ifndef __AMY_SHOW_DISCPLOT_H
#define __AMY_SHOW_DISCPLOT_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "opencv2/core/core.hpp"    

namespace amy 
{
// Class used to plot a colored disc in a 2D image.
class DiscPlot 
{
private:    
    cv::Mat image;
    // params
    int W;   // plot width (pixels)
    int H;   // plot height (pixels)  
    std::string plotName;
    // logic
    cv::Point center;           // disc center
    int radius;                   // disc radius (pixels)
    cv::Scalar colorGood;   // color for good state
    cv::Scalar colorBad;     // color for bad state   
    cv::Scalar colorText;     // color for text   
    // text configuration
    cv::Point textOrigin;       // origin position for the text
    int fontFace;
    double fontScale;
    int thickness;

public:
    DiscPlot();
     //~DiscPlot();

    // initializes plot with given size (creates image and window)
    void initPlot(int w, int h, std::string name);    
    // gets access to plotted image
    cv::Mat& getImage() {return image;};

    // draws disc representing the given state (good or bad)
    void drawDisc(bool bgood);
};
}    
#endif

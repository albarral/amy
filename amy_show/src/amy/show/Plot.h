#ifndef __AMY_SHOW_PLOT_H
#define __AMY_SHOW_PLOT_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "opencv2/core/core.hpp"    // for mat

namespace amy 
{
// Base class used to plot something in a fixed size image and show it in a window.
class Plot
{
protected:    
    // image
    cv::Mat image;
    int W;   // plot width (pixels)
    int H;   // plot height (pixels)
    int xaxis;     // position of x axis
    int yaxis;     // position of y axis
    std::string plotName;

public:
    Plot();
     //~Plot();

    // set plot sizes and name
    void setPlot(int w, int h, int posXaxis, int posYaxis, std::string name);
    // show the drawn image
    void show();
    // hides the drawn image
    void hide();
    
protected:        
    // draws the axes in the plot
    void drawAxes();
};
}    
#endif

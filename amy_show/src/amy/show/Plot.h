#ifndef __AMY_SHOW_PLOT_H
#define __AMY_SHOW_PLOT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"
#include "amy/utils/Record.h"

namespace amy 
{
// This class plots a record in a window (fixed size) and shows it.
class Plot
{
private:    
    static const int PLOT_W = 800;   // plot width (pixels)
    static const int PLOT_H = 400;   // plot width (pixels)
    static const int LEFT_MARGIN = 10;   // position of y axis (pixels)
    static const int MARGIN = 10;     // margin used in both limits (pixels)  

public:
    //Plot();       

    // plots the given record in a window
    static void plotRecord(Record& oRecord, int maxRange = 100);
    
private:    
    // draws the axes in the plot
    static void drawAxes(cv::Mat image, int POS_XAXIS, float yfactor);
};
}    
#endif

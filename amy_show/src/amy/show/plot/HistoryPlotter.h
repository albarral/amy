#ifndef __AMY_SHOW_HISTORYPLOTTER_H
#define __AMY_SHOW_HISTORYPLOTTER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/ShowData.h"
#include "tron2/tivy/SharedDisplay.h"
#include "tron2/tivy/plot/HistoryPlot.h"
#include "tron2/tivy/history/History2D.h"

namespace amy
{
// Class used to plot the evolution of arm signals (for debugging purpose).
class HistoryPlotter
{
private:
    // logic
    tron2::History2D oPanHistory2D;        // pan speed history
    tron2::HistoryPlot oPanHistoryPlot;    // plotting of pan speed
    tron2::History2D oTiltHistory2D;       // tilt speed history
    tron2::HistoryPlot oTiltHistoryPlot;    // plotting of tilt speed

public:
    HistoryPlotter();
    //~HistoryPlotter();

    // initialize plot
    void init(tron2::SharedDisplay& oSharedDisplay);
    // draw plot
    void draw(tron2::SharedDisplay& oSharedDisplay, ShowData* pShowData);    
};
}		
#endif

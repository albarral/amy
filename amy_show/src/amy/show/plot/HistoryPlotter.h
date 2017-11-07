#ifndef __AMY_SHOW_HISTORYPLOTTER_H
#define __AMY_SHOW_HISTORYPLOTTER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/ShowData.h"
#include "tivy/SharedDisplay.h"
#include "tivy/plot/HistoryPlot.h"
#include "tivy/history/History2D.h"

namespace amy
{
// Class used to plot the evolution of arm signals (for debugging purpose).
class HistoryPlotter
{
private:
    // logic
    tivy::History2D oPanHistory2D;        // pan speed history
    tivy::HistoryPlot oPanHistoryPlot;    // plotting of pan speed
    tivy::History2D oTiltHistory2D;       // tilt speed history
    tivy::HistoryPlot oTiltHistoryPlot;    // plotting of tilt speed

public:
    HistoryPlotter();
    //~HistoryPlotter();

    // initialize plot
    void init(tivy::SharedDisplay& oSharedDisplay);
    // draw plot
    void draw(tivy::SharedDisplay& oSharedDisplay, ShowData* pShowData);    
};
}		
#endif

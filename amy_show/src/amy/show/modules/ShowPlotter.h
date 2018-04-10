#ifndef __AMY_SHOW_SHOWPLOTTER_H
#define __AMY_SHOW_SHOWPLOTTER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/show/ShowData.h"
#include "amy/show/plot/ArmPlotter.h"
#include "amy/show/plot/HistoryPlotter.h"
#include "tron2/tivy/SharedDisplay.h"
#include "tron/control/module3.h"

namespace amy
{
// Module used to plot the arm's info
class ShowPlotter : public tron::Module3
{
private:
    static log4cxx::LoggerPtr logger;      
    ShowData* pShowData;     //  access to shared show data
    tron2::SharedDisplay oSharedDisplay;   // shared display (used to avoid X11 problems with different threads)
    ArmPlotter oArmPlotter;                      // plotter to draw arm position in display
    HistoryPlotter oHistoryPlotter;             // plotter to draw speed evolution in display

public:
    ShowPlotter();
    //~ShowPlotter();

    void init(ShowData& oShowData);
    
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
};
}		
#endif

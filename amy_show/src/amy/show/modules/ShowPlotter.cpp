/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/modules/ShowPlotter.h"

namespace amy
{
log4cxx::LoggerPtr ShowPlotter::logger(log4cxx::Logger::getLogger("amy.show"));

// Constructor 
ShowPlotter::ShowPlotter()
{    
    modName = "ShowPlotter";
    pShowData = 0;
    // init display
    oSharedDisplay.initDisplay();
 }

//ShowPlotter::~ShowPlotter()
//{
//}

void ShowPlotter::init(ShowData& oShowData)
{
    pShowData = &oShowData;    
}

void ShowPlotter::first()
{
    // init plotters
    oArmPlotter.init(oSharedDisplay);
    oHistoryPlotter.init(oSharedDisplay);
    LOG4CXX_INFO(logger, "ShowPlotter initialized");                                
}
                    
// drives the axis towards the target position
void ShowPlotter::loop()
{
    // exit if not enabled
    if (pShowData == 0)
    {
        LOG4CXX_ERROR(logger, "ShowPlotter: not enabled, loop ignored");
        return;
    }
    
    // draw images
    oArmPlotter.draw(oSharedDisplay, pShowData);
    oHistoryPlotter.draw(oSharedDisplay, pShowData);
    // show window
    oSharedDisplay.show();
}

}
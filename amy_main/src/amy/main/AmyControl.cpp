/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>

#include "amy/main/AmyControl.h"
#include "amy/core/robot/Arm.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr AmyControl::logger(Logger::getLogger("amy.main"));

// Constructor
AmyControl::AmyControl ()
{    
}

// Destructor
AmyControl::~AmyControl ()
{
}


bool AmyControl::launch(Robot& oRobot) 
{      
    bool bok = false;
    LOG4CXX_INFO(logger, "Launch amy control for robot " << oRobot.getName());
    
    // for now, just single arm robots supported
    if (oRobot.getNumArms() == 1)
    {
        Arm& oArm = oRobot.getListArms().at(0);
        
        // launch arm manager
        bok = oArmManager.launch(oArmBus, oArm);
    }
    else
    {
        LOG4CXX_WARN(logger, "For now, amy just supports single arm robots. Launch failed.");
        return false;        
    }
    
    return bok;
}

bool AmyControl::end()
{
    oArmManager.end();
}

bool AmyControl::checkEndRequested()
{
    return oArmBus.getCO_FINISH_MANAGER().checkRequested();
}

}




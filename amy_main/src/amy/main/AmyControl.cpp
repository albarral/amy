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
    
    float freq = oAmyConfig.getModulesFreq();
    
    // for now, just single arm robots supported
    if (oRobot.getNumArms() == 1)
    {
        // get controlled arm 
        Arm& oArm = oRobot.getListArms().at(0);        
        
        // init bus
        oArmBus.init(oArm);

        // launch arm manager
        int topLevel = 4;
        bok = oArmManager.launch(oArm, oArmBus, oAmyConfig, topLevel);
        
        // launch listener module
        oAmyListener.init(oArmBus);
        oAmyListener.setFrequency(freq);
        oAmyListener.on();
        
        // launch broadcaster module
        oAmyBroadcaster.init(oArmBus);
        oAmyBroadcaster.setFrequency(freq);
        oAmyBroadcaster.on();

        oSharedDisplay.initDisplay();
        
        // launch arm plotter module (for debug)
        oArmPlotter.connect(oArmBus);
        oArmPlotter.setFrequency(freq);
        oArmPlotter.shareDisplay(oSharedDisplay);
        oArmPlotter.on();
        
        // launch history plotter module (for debug)
        oHistoryPlotter.connect(oArmBus);
        oHistoryPlotter.setFrequency(freq);
        oHistoryPlotter.shareDisplay(oSharedDisplay);
        oHistoryPlotter.on();        

        // launch displayer module (for debug)
        oAmyDisplayer.setFrequency(freq);
        oAmyDisplayer.shareDisplay(oSharedDisplay);
        oAmyDisplayer.on();        
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
    // finish arm manager
    oArmManager.end();
    
    // finish listener module
    oAmyListener.off();
    oAmyListener.wait();      
    
    // finish broadcaster module
    oAmyBroadcaster.off();
    oAmyBroadcaster.wait();      

    // finish arm plotter module
    oArmPlotter.off();
    oArmPlotter.wait();      

    // finish history plotter module
    oHistoryPlotter.off();
    oHistoryPlotter.wait();      
    
    // finish displayer module 
    oAmyDisplayer.off();
    oAmyDisplayer.wait();
}

bool AmyControl::checkEndRequested()
{
    return oAmyListener.checkAmyEndRequested();
}

}




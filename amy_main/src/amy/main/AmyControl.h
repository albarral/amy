#ifndef __AMY_MAIN_AMYCONTROL_H
#define __AMY_MAIN_AMYCONTROL_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/core/config/AmyConfig.h"
#include "amy/core/robot/Robot.h"
#include "amy/arm/ArmManager.h"
#include "amy/main/AmyListener.h"
#include "amy/main/AmyBroadcaster.h"

namespace amy
{
// This class is used to control a robot's arms & hands.
// It instantiates the control bus and launches the arms & hands managers.
class AmyControl
{
    private:
        static log4cxx::LoggerPtr logger;
        AmyConfig oAmyConfig;
        ArmManager oArmManager;
        AmyListener oAmyListener;               // communications module for responding to external requests
        AmyBroadcaster oAmyBroadcaster;   // communications module for broadcasting the control info

    public:
        AmyControl();
        ~AmyControl();

       // launches the arm manager to handle the specified robot arm (returns false if something fails)
       bool launch(Robot& oRobot);
       // ends the arm manager
       bool end();

        // checks if finish command has been requested from console
        bool checkEndRequested();        
        
        // shows the present values of all bus elements
        void showBusState();
        
        // access arm manager
        ArmManager& getArmManager() {return oArmManager;};
};

}    
#endif

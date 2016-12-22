#ifndef __AMY_MAIN_AMYCONTROL_H
#define __AMY_MAIN_AMYCONTROL_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "amy/core/robot/Robot.h"
#include "amy/arm/ArmManager.h"
#include "amy/main/AmyListener.h"
//#include "amy/main/ArmComsOut.h"

namespace amy
{
// This class is used to control a robot's arms & hands.
// It instantiates the control bus and launches the arms & hands managers.
class AmyControl
{
    private:
        static log4cxx::LoggerPtr logger;
        ArmBus oArmBus;
        ArmManager oArmManager;
        AmyListener oAmyListener;
        //ArmComsOut oArmComsOut;   // communications module for sending outputs to network

    public:
        AmyControl();
        ~AmyControl();

       // launches the arm manager to handle the specified robot arm (returns false if something fails)
       bool launch(Robot& oRobot);
       // ends the arm manager
       bool end();

        // checks if finish command has been requested from console
        bool checkEndRequested();        
};

}    
#endif

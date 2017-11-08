#ifndef __AMY_COMS_AMYCOMSINFORMER_H
#define __AMY_COMS_AMYCOMSINFORMER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "amy/coms/out/ArmComsSensing.h"
#include "talky/coms/CommandBlock.h"
#include "talky/talk/Interpreter.h"

namespace amy
{
// Informer of amy sensor states to external processes.
// Builds communication messages with info obtained through the arm interface.
class AmyComsInformer
{    
private:
    static log4cxx::LoggerPtr logger;      
    bool bconnected;        // connected to amy control interfaces
    talky::Interpreter oInterpreter;     // message builder
    ArmComsSensing oArmComsSensing;
    talky::CommandBlock oCommandBlock1;  // commands block for arm info
//    talky::CommandBlock oCommandBlock2;  // commands block for arm info
//    talky::CommandBlock oCommandBlock3;  // commands block for arm info
    std::string messageJointAngles;               // raw message with joint angles
//    std::string messageJointStates;                // raw message with joint states
//    std::string messageAxes;                        // raw message with axes info
        
public:
    AmyComsInformer();

   bool isConnected() {return bconnected;};
   void connect2Arm(ArmBus& oArmBus);
               
    // fetch arm info and build messages with it
    bool getArmInfo();
    
    std::string getMessage4JointAngles() {return messageJointAngles;};
//    std::string getMessage4JointStates() {return messageJointStates;};
//    std::string getMessage4Axes() {return messageAxes;};
};
}
#endif

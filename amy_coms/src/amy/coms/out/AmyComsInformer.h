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
#include "talky/coms/CommandQueue.h"
#include "talky/talk/Interpreter.h"
#include "tuly/utils/MessageQueue.h"

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
    std::string messageJointAngles;               // raw message with joint angles    
    talky::CommandQueue oAxesCommandQueue;  // commands queue for axis category
    tuly::MessageQueue oAxesMessageQueue;       // messages queue for axis category
        
public:
    AmyComsInformer();

   bool isConnected() {return bconnected;};
   void connect2Arm(ArmBus& oArmBus);
               
    // fetch arm info and build messages with it
    bool getArmInfo();
    
    std::string getMessage4JointAngles() {return messageJointAngles;};
    tuly::MessageQueue& getMessageQueue4Axes() {return oAxesMessageQueue;};
    
private:
    void convertCommands2Messages(talky::CommandQueue& oCommandQueue, tuly::MessageQueue& oMessageQueue);
};
}
#endif

#ifndef __AMY_COMS_AMYCOMSSERVER_H
#define __AMY_COMS_AMYCOMSSERVER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/core/bus/ArmBus.h"
#include "amy/coms/sections/ArmComsControl.h"
#include "talky/talk/Interpreter.h"
#include "talky/coms/CommandBlock.h"

namespace amy
{
// Server for amy control requests from external processes.
// Interprets received messages and sends proper commands to arm interface.
class AmyComsServer
{    
private:
    static log4cxx::LoggerPtr logger;      
    bool bconnected;        // connected to amy control interfaces
    ArmBus* pArmBus;      // access to arm bus
    talky::Interpreter oInterpreter;     // message interpreter
    ArmComsControl oArmComsControl;     // sender of proper control commands to arm interface
        
public:
    AmyComsServer();

   bool isConnected() {return bconnected;};
   void connect2Arm(ArmBus& oArmBus);
      
    bool isAmyEndRequested();
         
   // interpret textual command, and send it properly to arm interface
    bool processMessage(std::string text); 

private:
    // transform interpreted command block to proper interface calls
    bool processCommandBlock(talky::CommandBlock& oCommandBlock);
};
}
#endif

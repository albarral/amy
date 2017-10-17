#ifndef __AMY_COMS_AMYCOMSSERVER_H
#define __AMY_COMS_AMYCOMSSERVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/coms/sections/ArmComsControl.h"
#include "amy/core/ifaces/iArmInterface.h"
#include "talky/talk/Interpreter.h"

namespace amy
{
// Base class used to serve requests from external processes.
// Implements the iAmyComs interface.
// Requests are transformed into proper calls to amy control interfaces (ie the ArmInterface)
class AmyComsServer
{    
private:
    static log4cxx::LoggerPtr logger;      
    bool bconnected;        // connected to amy control interfaces
    iArmInterface* pArmInterface;   // interface for arm control
    talky::Interpreter oInterpreter;     // message interpreter
    ArmComsControl oArmComsControl;     // control commands sender to arm interface
        
public:
    AmyComsServer();

   bool isConnected() {return bconnected;};
   void connect2Arm(iArmInterface* pArmInterface);
      
    bool isAmyEndRequested();
         
   // interprets textual command and if valid sends proper call to arm interface
    bool processMessage(std::string text); 
};
}
#endif

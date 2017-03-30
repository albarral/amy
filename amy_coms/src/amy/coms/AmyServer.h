#ifndef __AMY_COMS_AMYSERVER_H
#define __AMY_COMS_AMYSERVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/coms/ComsInterpreter.h"
#include "amy/coms/sections/JointServer.h"
#include "amy/coms/sections/AxisServer.h"
#include "amy/coms/sections/CyclicServer.h"
#include "amy/coms/sections/OtherServer.h"
#include "amy/core/ifaces/iArmInterface.h"

namespace amy
{
// Base class used to serve requests from external processes.
// Implements the iAmyComs interface.
// Requests are transformed into proper calls to amy control interfaces (ie the ArmInterface)
class AmyServer
{    
protected:
    static log4cxx::LoggerPtr logger;      
    bool bconnected;        // connected to amy control interfaces
    iArmInterface* pArmInterface;   // interface for arm control
    ComsInterpreter oComsInterpreter;   // commands interpreter
    // comms divided in section servers
    JointServer oJointServer;
    AxisServer oAxisServer;
    CyclicServer oCyclicServer;
    OtherServer oOtherServer;    
        
public:
    AmyServer();

   bool isConnected() {return bconnected;};
   void connect2Arm(iArmInterface& oArmInterface);
      
    bool isAmyEndRequested();
         
   // interprets textual command and if valid sends proper call to arm interface
    bool processCommand(std::string text); 
};
}
#endif

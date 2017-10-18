#ifndef __AMY_COMS_AMYCOMSINFORMER_H
#define __AMY_COMS_AMYCOMSINFORMER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/core/ifaces/iArmInterface.h"
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
    iArmInterface* pArmInterface;   // arm interface
    talky::Interpreter oInterpreter;     // message builder
    talky::CommandBlock oCommandBlock;  // arm info is stored in the form of commands block
        
public:
    AmyComsInformer();

   bool isConnected() {return bconnected;};
   void connect2Arm(iArmInterface* pArmInterface);
               
    // fetch arm info and build message with it
    std::string getArmInfo();
};
}
#endif

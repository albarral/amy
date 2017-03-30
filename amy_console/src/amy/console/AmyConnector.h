#ifndef __AMY_CONSOLE_AMYCONNECTOR_H
#define __AMY_CONSOLE_AMYCONNECTOR_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/coms/AmyClient.h"

namespace amy
{
// Class that sends requests to the amy process through an amy coms client.
class AmyConnector
{
private:
    static log4cxx::LoggerPtr logger;
    AmyClient* pAmyClient;     // amy client   

public:
    AmyConnector();
    ~AmyConnector();

    // connect to amy process
    void connect2Amy();                
    // sends command to amy process
    bool sendCommand(int category, int action, float value);    
    
private:
    // sends joint command to amy process
    bool sendJointCommand(int action, float value);    
    // sends axis command to amy process
    bool sendAxisCommand(int action, float value);    
    // sends cyclic command to amy process
    bool sendCyclicCommand(int action, float value);    
    // sends other command to amy process
    bool sendOtherCommand(int action, float value);    
    
};
}		
#endif

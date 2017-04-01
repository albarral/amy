#ifndef __AMY_COMS_AMYCLIENT_H
#define __AMY_COMS_AMYCLIENT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/coms/sections/JointClient.h"
#include "amy/coms/sections/AxisClient.h"
#include "amy/coms/sections/CyclicClient.h"
#include "amy/coms/sections/OtherClient.h"

namespace amy
{
// Base class used to transmit requests to the amy control process.
// Derived classes must implement the sendCommand() method.
class AmyClient
{    
private:
    JointClient oJointClient;
    AxisClient oAxisClient;
    CyclicClient oCyclicClient;
    OtherClient oOtherClient;    
    
public:
    AmyClient();

    JointClient& getJointClient() {return oJointClient;};
    AxisClient& getAxisClient() {return oAxisClient;};
    CyclicClient& getCyclicClient() {return oCyclicClient;};
    OtherClient& getOtherClient() {return oOtherClient;};

    void sendJointCommand();
    void sendAxisCommand();
    void sendCyclicCommand();
    void sendOtherCommand();
    
    // dummy method for to do commands
    void toDoCommand();
    
    virtual void setPort(const int port) = 0;

protected:
    // command sending method specific for each AmyClient implementation
    virtual void sendCommand(std::string text) = 0;
    
};
}
#endif

#ifndef __AMY_CLIENT_AMYCLIENT_H
#define __AMY_CLIENT_AMYCLIENT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "amy/coms/iAmyComs.h"
#include "amy/coms/AmyCommand.h"

namespace amy
{
// Base class used to transmit requests to the amy control process.
// Implements the iAmyComs interface. 
// Method to implement by derived classes:
// - sendCommand()    
class AmyClient : public iAmyComs
{    
protected:
    AmyCommand oAmyCommand; // command structure to be sent
    
public:
    AmyClient();

    AmyCommand& getAmyCommand() {return oAmyCommand;};
    
    virtual void movePan(float value);
    virtual void moveTilt(float value);
    virtual void moveRadius(float value);

    virtual void setPosHS(float value);
    virtual void setPosVS(float value);
    virtual void setPosELB(float value);
    virtual void setPosHW(float value);
    virtual void setPosVW(float value);
    
    virtual void endAmy();
    
protected:
    // send command
    virtual void sendCommand() = 0;
};
}
#endif

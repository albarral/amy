#ifndef __AMY_COMS_AMYCLIENT_H
#define __AMY_COMS_AMYCLIENT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "amy/coms/AmyCommand.h"

namespace amy
{
// Base class used to transmit requests to the amy control process.
// Method to implement by derived classes:
// - sendCommand()    
class AmyClient
{    
protected:
    AmyCommand oAmyCommand; // command structure to be sent
    
public:
    AmyClient();

    AmyCommand& getAmyCommand() {return oAmyCommand;};
    
    void movePan(float value);
    void moveTilt(float value);
    void moveRadius(float value);

    void setPosHS(float value);
    void setPosVS(float value);
    void setPosELB(float value);
    void setPosHW(float value);
    void setPosVW(float value);
    
    void endAmy();
    
protected:
    // send command
    virtual void sendCommand() = 0;
};
}
#endif

#ifndef __AMY_COMS_AMYCLIENT_H
#define __AMY_COMS_AMYCLIENT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "amy/coms/iAmyComs.h"
#include "amy/coms/data/AmyCommand.h"

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

    virtual void panFrequency(float value);
    virtual void panAmplitude(float value);
    virtual void panTrigger();
    virtual void panStop();

    // axis speeds        
    virtual void panSpeed(float value);
    virtual void tiltSpeed(float value);
    virtual void radialSpeed(float value);
    virtual void keepTilt(int value);    

    // axis positions   
    virtual void movePan(float value);
    virtual void moveTilt(float value);
    virtual void moveRadius(float value);
        
    // joint positions
    virtual void setPosHS(float value);
    virtual void setPosVS(float value);
    virtual void setPosELB(float value);
    virtual void setPosHW(float value);
    virtual void setPosVW(float value);
    
    // amy commands   
    virtual void endAmy();
    
    // dummy method for to do commands
    virtual void toDoCommand();
    
protected:
    // command sending method specific for each AmyClient implementation
    virtual void sendCommand() = 0;
};
}
#endif

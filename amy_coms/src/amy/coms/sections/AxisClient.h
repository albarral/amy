#ifndef __AMY_COMS_AXISCLIENT_H
#define __AMY_COMS_AXISCLIENT_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/coms/ifaces/iComsAxes.h"
#include "amy/coms/data/AxisCommand.h"

namespace amy
{
// Class used to send requests for axes control.
class AxisClient : public iComsAxes
{    
private:
    std::string text;
    
public:
    AxisClient();

    std::string getCommand() {return text;};
    
    // axis speeds        
    virtual void panSpeed(float value);
    virtual void tiltSpeed(float value);
    virtual void radialSpeed(float value);
    // axis positions   
    virtual void movePan(float value);
    virtual void moveTilt(float value);
    virtual void moveRadius(float value);

private:
    // obtains the textual form of the given command
    void updateText(AxisCommand& oAxisCommand);
};
}
#endif

#ifndef __AMY_COMS_OTHERCLIENT_H
#define __AMY_COMS_OTHERCLIENT_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/coms/ifaces/iComsOthers.h"
#include "amy/coms/data/OtherCommand.h"


namespace amy
{
// Class used to send requests for some amy controls.
class OtherClient : public iComsOthers
{    
private:
    std::string text;
    
public:
    OtherClient();

    std::string getCommand() {return text;};
    
    // keep tilt
    virtual void keepTilt(int value);                
    // amy commands   
    virtual void endAmy();
private:
    // obtains the textual form of the given command
    void updateText(OtherCommand& oOtherCommand);
};
}
#endif

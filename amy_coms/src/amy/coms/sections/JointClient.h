#ifndef __AMY_COMS_JOINTCLIENT_H
#define __AMY_COMS_JOINTCLIENT_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/coms/ifaces/iComsJoints.h"
#include "amy/coms/data/JointCommand.h"

namespace amy
{
// Class used to send requests for joints control.
class JointClient : public iComsJoints
{    
private:
    std::string text;
    
public:
    JointClient();

    std::string getCommand() {return text;};
    
    // joint positions
    virtual void setPosHS(float value);
    virtual void setPosVS(float value);
    virtual void setPosELB(float value);
    virtual void setPosHW(float value);
    virtual void setPosVW(float value);    
private:
    // obtains the textual form of the given command
    void updateText(JointCommand& oJointCommand);
};
}
#endif

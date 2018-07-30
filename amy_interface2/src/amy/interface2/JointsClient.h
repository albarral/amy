#ifndef __AMY_INTERFACE2_JOINTSCLIENT_H
#define __AMY_INTERFACE2_JOINTSCLIENT_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron/coms/ComsSender.h"

namespace amy
{
// Joints section client to control a robot arm.
// Extends from tron ComsSender    
class JointsClient : public tron::ComsSender
{            
public:
    JointsClient();
    //~JointsClient();

    // set HS joint (horizontal shoulder) to given position (degrees)
    bool setHS(float value);
    // set VS joint (vertical shoulder) to given position (degrees)
    bool setVS(float value);
    // set ELB joint (elbow) to given position (degrees)
    bool setELB(float value);
    // set HWRI joint (horizontal wrist) to given position (degrees)
    bool setHWRI(float value);
    // set VWRI joint (vertical wrist) to given position (degrees)
    bool setVWRI(float value);    
};

}
#endif

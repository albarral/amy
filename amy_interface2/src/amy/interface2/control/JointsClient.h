#ifndef __AMY_INTERFACE2_JOINTSCLIENT_H
#define __AMY_INTERFACE2_JOINTSCLIENT_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "tron/coms/ComsSender.h"
#include "tron/coms/ChannelWriter.h"

namespace amy
{
// Joints section client to control a robot arm.
// Uses tron ComsSender for communications
class JointsClient
{            
private:
    static log4cxx::LoggerPtr logger;
    tron::ComsSender oComsSender;   // communications object
    tron::ChannelWriter* pHSChannel;    // channel writer for HS joint
    tron::ChannelWriter* pVSChannel;    // channel writer for VS joint
    tron::ChannelWriter* pELBChannel;   // channel writer for ELB joint
    tron::ChannelWriter* pHWRIChannel;  // channel writer for HWRI joint
    tron::ChannelWriter* pVWRIChannel;  // channel writer for VWRI joint

public:
    JointsClient();
    //~JointsClient();

    // set HS joint to given position (degrees)
    bool setHS(float value);
    // set VS joint to given position (degrees)
    bool setVS(float value);
    // set ELB joint to given position (degrees)
    bool setELB(float value);
    // set HWRI joint to given position (degrees)
    bool setHWRI(float value);
    // set VWRI joint to given position (degrees)
    bool setVWRI(float value);    
};

}
#endif

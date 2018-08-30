#ifndef __AMY_INTERFACE2_JOINTSINFORMER_H
#define __AMY_INTERFACE2_JOINTSINFORMER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "tron/coms/ComsSender.h"
#include "tron/coms/ChannelWriter.h"

namespace amy
{
// Broadcaster of joints section info of a robot arm.
// Uses tron ComsSender for communications
class JointsInformer
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
    JointsInformer();
    //~JointsInformer();

    // send HS joint position (degrees)
    bool sendHS(float value);
    // send VS joint position (degrees)
    bool sendVS(float value);
    // send ELB joint position (degrees)
    bool sendELB(float value);
    // send HWRI joint position (degrees)
    bool sendHWRI(float value);
    // send VWRI joint position (degrees)
    bool sendVWRI(float value);    
};

}
#endif

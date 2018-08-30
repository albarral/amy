#ifndef __AMY_INTERFACE2_JOINTSLISTENER_H
#define __AMY_INTERFACE2_JOINTSLISTENER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "tron/coms/ComsReceiver.h"
#include "tron/coms/ChannelReader.h"

namespace amy
{
// Listener of joints section info of a robot arm.
// Uses tron ComsReceiver for communications    
class JointsListener
{            
private:
    static log4cxx::LoggerPtr logger;
    tron::ComsReceiver oComsReceiver;  // communications object     
    tron::ChannelReader* pHSChannel;    // channel reader for HS joint
    tron::ChannelReader* pVSChannel;    // channel reader for VS joint
    tron::ChannelReader* pELBChannel;   // channel reader for ELB joint
    tron::ChannelReader* pHWRIChannel;  // channel reader for HWRI joint
    tron::ChannelReader* pVWRIChannel;  // channel reader for VWRI joint

public:
    JointsListener();
    //~JointsListener();

    // sense HS joint position (degrees)
    bool senseHS(float& value);
    // sense VS joint position (degrees)
    bool senseVS(float& value);
    // sense ELB joint position (degrees)
    bool senseELB(float& value);
    // sense HWRI joint position (degrees)
    bool senseHWRI(float& value);
    // sense VWRI joint position (degrees)
    bool senseVWRI(float& value);    
};

}
#endif

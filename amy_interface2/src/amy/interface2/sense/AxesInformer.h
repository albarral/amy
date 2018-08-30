#ifndef __AMY_INTERFACE2_AXESINFORMER_H
#define __AMY_INTERFACE2_AXESINFORMER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "tron/coms/ComsSender.h"
#include "tron/coms/ChannelWriter.h"

namespace amy
{
// Broadcaster of axes section info of a robot arm.
// Uses tron ComsSender for communications
class AxesInformer
{            
private:
    static log4cxx::LoggerPtr logger;
    tron::ComsSender oComsSender;   // communications object
    tron::ChannelWriter* pPanChannel;    // channel writer for Pan axis
    tron::ChannelWriter* pTiltChannel;    // channel writer for Tilt axis
    tron::ChannelWriter* pRadialChannel;   // channel writer for Radial axis
    tron::ChannelWriter* pPanSpeedChannel;  // channel writer for Pan speed
    tron::ChannelWriter* pTiltSpeedChannel;  // channel writer for Tilt speed
    tron::ChannelWriter* pRadialSpeedChannel;  // channel writer for Radial speed

public:
    AxesInformer();
    //~AxesInformer();

    // send Pan axis position (degrees)
    bool sendPan(float value);
    // send Tilt axis position (degrees)
    bool sendTilt(float value);
    // send Radial axis position (cm)
    bool sendRadial(float value);
    // send Pan speed (degrees/s)
    bool sendPanSpeed(float value);
    // send Tilt speed (degrees/s)
    bool sendTiltSpeed(float value);    
    // send Radial speed (cm/s)
    bool sendRadialSpeed(float value);    
};

}
#endif

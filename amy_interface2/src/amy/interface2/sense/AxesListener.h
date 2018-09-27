#ifndef __AMY_INTERFACE2_AXESLISTENER_H
#define __AMY_INTERFACE2_AXESLISTENER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "tron/interface/SectionListener.h"
#include "tron/coms/ChannelReader.h"

namespace amy
{
// Listener of axes section info of a robot arm.
class AxesListener : public tron::SectionListener
{            
private:
    static log4cxx::LoggerPtr logger;
    tron::ChannelReader* pPanChannel;    // channel reader for Pan axis
    tron::ChannelReader* pTiltChannel;    // channel reader for Tilt axis
    tron::ChannelReader* pRadialChannel;   // channel reader for Radial axis
    tron::ChannelReader* pPanSpeedChannel;  // channel reader for Pan speed
    tron::ChannelReader* pTiltSpeedChannel;  // channel reader for Tilt speed
    tron::ChannelReader* pRadialSpeedChannel;  // channel reader for Radial speed 

public:
    AxesListener();
    //~AxesListener();

    // sense Pan axis position (degrees)
    bool sensePan(float& value);
    // sense Tilt axis position (degrees)
    bool senseTilt(float& value);
    // sense Radial axis position (degrees)
    bool senseRadial(float& value);
    // sense PanSpeed axis position (degrees)
    bool sensePanSpeed(float& value);
    // sense TiltSpeed axis position (degrees)
    bool senseTiltSpeed(float& value);    
    // sense RadialSpeed axis position (degrees)
    bool senseRadialSpeed(float& value);    
};

}
#endif

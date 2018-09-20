#ifndef __AMY_INTERFACE2_AXESSERVER2_H
#define __AMY_INTERFACE2_AXESSERVER2_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "tron/interface/SectionServer.h"
#include "tron/coms/ChannelReader.h"

namespace amy
{
// Axes section server to control a robot arm.
// Uses tron ComsReceiver for communications    
class AxesServer2 : public tron::SectionServer
{            
private:
    static log4cxx::LoggerPtr logger2;
    tron::ChannelReader* pPanChannel;    // channel reader for Pan axis
    tron::ChannelReader* pTiltChannel;    // channel reader for Tilt axis
    tron::ChannelReader* pRadialChannel;   // channel reader for Radial axis
    tron::ChannelReader* pPanSpeedChannel;  // channel reader for Pan axis speed
    tron::ChannelReader* pTiltSpeedChannel;  // channel reader for Tilt axis speed
    tron::ChannelReader* pRadialSpeedChannel;  // channel reader for Radial axis speed 
    tron::ChannelReader* pKeepTiltChannel;  // channel reader for keep tilt behaviour

public:
    AxesServer2();
    //~AxesServer2();

    // get received Pan axis position (degrees)
    bool getPan(float& value);
    // get received Tilt axis position  (degrees)
    bool getTilt(float& value);
    // get received Radial axis position  (cm)
    bool getRadial(float& value);
    // get received  Pan axis speed (degrees/s)
    bool getPanSpeed(float& value);
    // get received  Tilt axis speed  (degrees/s)
    bool getTiltSpeed(float& value);    
    // get received  Radial axis speed (cm/s)
    bool getRadialSpeed(float& value);    
    // get received keep tilt (flag))
    bool getKeepTilt(bool& value);    
};

}
#endif

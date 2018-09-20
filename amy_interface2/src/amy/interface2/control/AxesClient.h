#ifndef __AMY_INTERFACE2_AXESCLIENT_H
#define __AMY_INTERFACE2_AXESCLIENT_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "tron/interface/SectionClient.h"
#include "tron/coms/ChannelWriter.h"

namespace amy
{
// Axes section client to control a robot arm.
// Uses tron ComsSender for communications
class AxesClient : public tron::SectionClient
{            
private:
    static log4cxx::LoggerPtr logger2;
    tron::ChannelWriter* pPanChannel;    // channel writer for Pan axis
    tron::ChannelWriter* pTiltChannel;    // channel writer for Tilt axis
    tron::ChannelWriter* pRadialChannel;   // channel writer for Radial axis
    tron::ChannelWriter* pPanSpeedChannel;  // channel writer for Pan axis Speed 
    tron::ChannelWriter* pTiltSpeedChannel;  // channel writer for Tilt axis Speed
    tron::ChannelWriter* pRadialSpeedChannel;  // channel writer for Radial axis Speed 
    tron::ChannelWriter* pKeepTiltChannel;  // channel writer for keep tilt behaviour

public:
    AxesClient();
    //~AxesClient();

    // set Pan axis to given position (degrees)
    bool setPan(float value);
    // set Tilt axis to given position (degrees)
    bool setTilt(float value);
    // set Radial axis to given position (cm)
    bool setRadial(float value);
    // set speed of Pan axis (degrees/s)
    bool setPanSpeed(float value);
    // set speed of Tilt axis (degrees/s)
    bool setTiltSpeed(float value);    
    // set speed of radial axis (cm/s)
    bool setRadialSpeed(float value);    
    // keep arm tilt
    bool keepTilt();    
};

}
#endif

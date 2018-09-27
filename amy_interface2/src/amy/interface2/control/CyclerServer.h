#ifndef __AMY_INTERFACE2_CYCLERSERVER_H
#define __AMY_INTERFACE2_CYCLERSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "tron/interface/SectionServer.h"
#include "tron/coms/ChannelReader.h"

namespace amy
{
// Cycler section server to control a robot arm.
// Various cycler sections exist, so server must be tuned to one of them.
class CyclerServer : public tron::SectionServer
{            
private:
    static log4cxx::LoggerPtr logger2;
    std::string serverName;
    int targetCycler;       // defines which cycler is controlled
    // main component
    tron::ChannelReader* pFreq1Channel;    // channel reader for main frequency
    tron::ChannelReader* pAmp1Channel;    // channel reader for main amplitude
    tron::ChannelReader* pAngle1Channel;   // channel reader for main angle
    tron::ChannelReader* pPhase1Channel;  // channel reader for main phase
    // secondary component
    tron::ChannelReader* pFreq2Channel;    // channel reader for secondary frequency
    tron::ChannelReader* pAmp2Channel;    // channel reader for secondary amplitude
    tron::ChannelReader* pAngle2Channel;   // channel reader for secondary angle
    tron::ChannelReader* pPhase2Channel;  // channel reader for secondary phase
    // common channel
    tron::ChannelReader* pRunChannel;  // channel reader for start/stop action

public:
    CyclerServer();
    //~CyclerServer();

    // tune server to given cycler (connect channels to proper topics)
    bool tune2Cycler(int i);

    // get frequency of main cycler component (Hz)
    bool getMainFreq(float& value);
    // get amplitude of main cycler component (degrees)
    bool getMainAmplitude(float& value);
    // get angle of main cycler component (degrees)
    bool getMainAngle(float& value);
    // get phase of main cycler component (degrees)
    bool getMainPhase(float& value);
    
    // get frequency of secondary cycler component (Hz)
    bool getSecondaryFreq(float& value);
    // get amplitude of secondary cycler component (degrees)
    bool getSecondaryAmplitude(float& value);
    // get angle of secondary cycler component (degrees)
    bool getSecondaryAngle(float& value);
    // get phase of secondary cycler component (degrees)
    bool getSecondaryPhase(float& value);
    
    // get start or stop command for cycler movement
    bool getAction(int& value);    
};

}
#endif

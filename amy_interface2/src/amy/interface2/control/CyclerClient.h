#ifndef __AMY_INTERFACE2_CYCLERCLIENT_H
#define __AMY_INTERFACE2_CYCLERCLIENT_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "tron/coms/ComsSender.h"
#include "tron/coms/ChannelWriter.h"

namespace amy
{
// Cycler section client to control a robot arm.
// Various cycler sections exist, so client must be tuned to one of them.
// Uses tron ComsSender for communications
class CyclerClient
{            
private:
    static log4cxx::LoggerPtr logger;
    std::string clientName;
    bool btuned;            // client tuned to one cycler
    int targetCycler;       // defines which cycler is controlled
    tron::ComsSender oComsSender;   // communications object
    // main component
    tron::ChannelWriter* pFreq1Channel;    // channel writer for main frequency
    tron::ChannelWriter* pAmp1Channel;    // channel writer for main amplitude
    tron::ChannelWriter* pAngle1Channel;   // channel writer for main angle
    tron::ChannelWriter* pPhase1Channel;  // channel writer for main phase
    // secondary component
    tron::ChannelWriter* pFreq2Channel;    // channel writer for secondary frequency
    tron::ChannelWriter* pAmp2Channel;    // channel writer for secondary amplitude
    tron::ChannelWriter* pAngle2Channel;   // channel writer for secondary angle
    tron::ChannelWriter* pPhase2Channel;  // channel writer for secondary phase
    // common channel
    tron::ChannelWriter* pRunChannel;  // channel writer for start/stop action

public:
    CyclerClient();
    //~CyclerClient();

    bool isTuned() {return btuned;};
    // tune client to given cycler (connect channels to proper topics)
    bool tune2Cycler(int i);
    
    // set frequency of main cycler component (Hz))
    bool setMainFreq(float value);
    // set amplitude of main cycler component (degrees)
    bool setMainAmplitude(float value);
    // set angle of main cycler component (degrees)
    bool setMainAngle(float value);
    // set phase of main cycler component (degrees)
    bool setMainPhase(float value);
    
    // set frequency of secondary cycler component (Hz))
    bool setSecondaryFreq(float value);
    // set amplitude of secondary cycler component (degrees)
    bool setSecondaryAmplitude(float value);
    // set angle of secondary cycler component (degrees)
    bool setSecondaryAngle(float value);
    // set phase of secondary cycler component (degrees)
    bool setSecondaryPhase(float value);
    
    // start or stop cycler movement
    bool run(bool bvalue);
};

}
#endif

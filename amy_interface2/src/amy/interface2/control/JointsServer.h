#ifndef __AMY_INTERFACE2_JOINTSSERVER_H
#define __AMY_INTERFACE2_JOINTSSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "tron/interface/SectionServer.h"
#include "tron/coms/ChannelReader.h"

namespace amy
{
// Joints section server to control a robot arm.
class JointsServer : public tron::SectionServer
{            
private:
    static log4cxx::LoggerPtr logger2;
    tron::ChannelReader* pHSChannel;    // channel reader for HS joint
    tron::ChannelReader* pVSChannel;    // channel reader for VS joint
    tron::ChannelReader* pELBChannel;   // channel reader for ELB joint
    tron::ChannelReader* pHWRIChannel;  // channel reader for HWRI joint
    tron::ChannelReader* pVWRIChannel;  // channel reader for VWRI joint

public:
    JointsServer();
    //~JointsServer();

    // get HS joint position received command (degrees)
    bool getHS(float& value);
    // get VS joint position received command (degrees)
    bool getVS(float& value);
    // get ELB joint position received command (degrees)
    bool getELB(float& value);
    // get HWRI joint position received command (degrees)
    bool getHWRI(float& value);
    // get VWRI joint position received command (degrees)
    bool getVWRI(float& value);    
};

}
#endif

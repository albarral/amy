#ifndef __AMY_INTERFACE_ARMCLIENT_H
#define __AMY_INTERFACE_ARMCLIENT_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "tron2/coms/ChannelClient.h"
#include "tron2/coms/ifaces/TronAnyClient.h"

namespace amy
{
// Arm client class to control a robot arm.
class ArmClient : public tron2::TronAnyClient
{    
private:
    static log4cxx::LoggerPtr logger;
    tron2::ChannelClient oJointChannelClient;
    tron2::ChannelClient oAxisChannelClient;
    tron2::ChannelClient oCycler1ChannelClient;
    tron2::ChannelClient oCycler2ChannelClient;
    tron2::ChannelClient oExtraChannelClient;
        
public:
    ArmClient();
    ~ArmClient();

    // set HS joint (horizontal shoulder) to given position (degrees)
    bool setHS(float value);
    // set VS joint (vertical shoulder) to given position (degrees)
    bool setVS(float value);
    // set ELB joint (elbow) to given position (degrees)
    bool setELB(float value);
    // set HWRI joint (horizontal wrist) to given position (degrees)
    bool setHWRI(float value);
    // set VWRI joint (vertical wrist) to given position (degrees)
    bool setVWRI(float value);    
    
    // axis topic ...
    // set pan axis to given position (degrees)
    bool setPan(float value);
    // set tilt axis to given position (degrees)
    bool setTilt(float value);
    // set radial axis to given position (cm)
    bool setRadial(float value);
    // move pan axis at given speed (degrees/s)
    bool setPanSpeed(float value);
    // move tilt axis at given speed (degrees/s)
    bool setTiltSpeed(float value);
    // move radial axis at given speed (cm/s)
    bool setRadialSpeed(float value);
    // keep arm tilt
    bool keepTilt();

    // cycler1 topic ...
    // set amplitude of cycler1 main component (degrees)
    bool setCycler1MainAmp(float value);
    // set angle of cycler1 main component (degrees)
    bool setCycler1MainAngle(float value);
    // set frequency of cycler1 main component (Hz)
    bool setCycler1MainFreq(float value);
    // set phase of cycler1 main component (degrees)
    bool setCycler1MainPhase(float value);
    // set amplitude of cycler1 secondary component (degrees)
    bool setCycler1SecAmp(float value);
    // set angle of cycler1 secondary component (degrees)
    bool setCycler1SecAngle(float value);
    // set frequency of cycler1 secondary component (Hz)
    bool setCycler1SecFreq(float value);
    // set phase of cycler1 secondary component (degrees)
    bool setCycler1SecPhase(float value);
    // starts or stops cycler1 movement
    bool setCycler1Action(int value);

    // cycler2 topic ...
    // set amplitude of cycler2 main component (degrees)
    bool setCycler2MainAmp(float value);
    // set angle of cycler2 main component (degrees)
    bool setCycler2MainAngle(float value);
    // set frequency of cycler2 main component (Hz)
    bool setCycler2MainFreq(float value);
    // set phase of cycler2 main component (degrees)
    bool setCycler2MainPhase(float value);
    // set amplitude of cycler2 secondary component (degrees)
    bool setCycler2SecAmp(float value);
    // set angle of cycler2 secondary component (degrees)
    bool setCycler2SecAngle(float value);
    // set frequency of cycler2 secondary component (Hz)
    bool setCycler2SecFreq(float value);
    // set phase of cycler2 secondary component (degrees)
    bool setCycler2SecPhase(float value);
    // starts or stops cycler2 movement
    bool setCycler2Action(int value);

    // extra topic ...    
    // full stop of control actions 
    virtual bool fullStop();
    // end control process
    virtual bool endNode();        
};

}
#endif

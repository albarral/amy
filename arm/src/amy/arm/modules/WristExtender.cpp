/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "log4cxx/ndc.h"

#include "amy/arm/modules/WristExtender.h"
#include "amy/arm/modules/JointMover.h"

using namespace log4cxx;

namespace amy
{
WristExtender::WristExtender()
{
    modName = "WristExtender";
    pBusEL = 0;
}

//WristExtender::~WristExtender()
//{
//}

void WristExtender::selectBusJoint()
{
    pBusEL = &pBus->getBusEL();
}

void WristExtender::senseBus()
{
    if (pBus->getCO_WRIST_RADIUS().checkRequested())
        targetValue = (int)pBus->getCO_WRIST_RADIUS().getValue();
    
    istValue = pBusEL->getCO_JOINT_ANGLE().getValue();  // last commanded elbow angle    
    lastAction = pBusEL->getCO_JMOVER_ACTION().getValue();     // last commanded elbow action        
    lastSpeed = pBusEL->getCO_JMOVER_SPEED().getValue();       // last commanded elbow speed
}

// x moves done by horizontal shoulder
// y moves done by elbow
void WristExtender::writeBus()
{  
    // send if action <> lastAction or speed <> lastSpeed
    
    int action = 0;
    float v = 0;

    pBusEL->getCO_JMOVER_SPEED().request(v);
    pBusEL->getCO_JMOVER_ACTION().request(action);
}

void WristExtender::doDriveControl(float dist)
{
    if (dist > 0)
        outAction = JointMover::eMOV_NEGATIVE;
    else 
        outAction = JointMover::eMOV_POSITIVE;
    
    outSpeed = vH;        
}

void WristExtender::doApproachControl(float dist)
{
}

void WristExtender::doArrivedControl(float dist)
{
}

}
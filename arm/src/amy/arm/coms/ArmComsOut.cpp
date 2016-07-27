/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "ArmComsOut.h"
#include "amy/arm/coms/ArmCommand.h"
#include "amy/arm/config/ArmConfig.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmComsOut::logger(Logger::getLogger("amy.arm"));

// Constructor 
ArmComsOut::ArmComsOut ()
{    
    benabled = false;
    bconnected = false;
    pBus = 0;
    pBusHShoulder = 0;
    pBusVShoulder = 0;
    pBusElbow = 0;
    pBusWrist = 0;    
    for (int i=0; i<AMY_MAX_JOINTS; i++)
      lastAngles[i] = 0.0;
 }

// Destructor
ArmComsOut::~ArmComsOut ()
{
}

void ArmComsOut::init (int numJoints)
{
    this->numJoints = numJoints;
    // initialize network access
    if (oArmNetwork.init(ArmNetwork::eNETWORK_DB))
    {
        benabled = true;    
        LOG4CXX_INFO(logger, "ArmComsOut initialized (network type is DB)");          
    }
    else    
        LOG4CXX_ERROR(logger, "ArmComsOut init failed");          
};

void ArmComsOut::connect(ArmBus& oBus)
{
    pBus = &oBus;
    pBusHShoulder = &pBus->getJointBus(ArmConfig::horizontal_shoulder);
    pBusVShoulder = &pBus->getJointBus(ArmConfig::vertical_shoulder);
    pBusElbow = &pBus->getJointBus(ArmConfig::elbow);
    pBusWrist = &pBus->getJointBus(ArmConfig::vertical_wrist);
    bconnected = true;

    LOG4CXX_DEBUG(logger, "ArmComsOut connected to bus");      
}

void ArmComsOut::first()
{    
    log4cxx::NDC::push("ArmComsOut");   	
}

void ArmComsOut::loop()
{    
    bool bchanged = false;
    
    // get joint control values ...    
    // h shoulder
    pBusHShoulder->getCO_JOINT_ANGLE().getValue(angles[0]);
    // v shoulder
    pBusVShoulder->getCO_JOINT_ANGLE().getValue(angles[1]);
    // elbow
    pBusElbow->getCO_JOINT_ANGLE().getValue(angles[2]);
    // wrist
    pBusWrist->getCO_JOINT_ANGLE().getValue(angles[3]);

    // check if they have changed 
    for (int i=0; i<numJoints; i++)
    {
        if (angles[i] != lastAngles[i])
        {
            lastAngles[i] = angles[i];
            bchanged = true;
        }
    }
    
    // if so send them to network
    if (bchanged)
    {
        oArmData.setSoll1(angles[0]);
        oArmData.setSoll2(angles[1]);
        oArmData.setSoll3(angles[2]);
        oArmData.setSoll4(angles[3]);
        oArmNetwork.setArmSoll(0, oArmData);
    }
}

}
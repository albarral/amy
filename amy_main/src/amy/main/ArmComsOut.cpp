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
    modName = "ArmComsOut";
    pBusHShoulder = 0;
    pBusVShoulder = 0;
    pBusElbow = 0;
    pBusVWrist = 0;    
    for (int i=0; i<AMY_MAX_JOINTS; i++)
      lastAngles[i] = 0.0;
 }

// Destructor
ArmComsOut::~ArmComsOut ()
{
}

void ArmComsOut::init(Arm& oArm)
{
    numJoints = oArm.getNumJoints();
    // initialize network access
    if (oArmNetwork.init(ArmNetwork::eNETWORK_DB))
    {
        benabled = true;    
        LOG4CXX_INFO(logger, modName << " initialized (network type is DB)");          
    }
    else    
        LOG4CXX_ERROR(logger, modName << " init failed");          
};

void ArmComsOut::connect(ArmBus& oBus)
{
    pBusHShoulder = &oBus.getBusHS();
    pBusVShoulder = &oBus.getBusVS();
    pBusElbow = &oBus.getBusEL();
    pBusVWrist = &oBus.getBusVW();
    
    ArmModule::connect(oBus);
}

void ArmComsOut::first()
{    
    log4cxx::NDC::push(modName);   	
}

void ArmComsOut::loop()
{    
    bool bchanged = false;
    
    // read joints control values ...    
    
    // h shoulder
    angles[0] = pBusHShoulder->getCO_JOINT_ANGLE().getValue();
    // v shoulder
    angles[1] = pBusVShoulder->getCO_JOINT_ANGLE().getValue();
    // elbow
    angles[2] = pBusElbow->getCO_JOINT_ANGLE().getValue();
    // wrist
    angles[3] = pBusVWrist->getCO_JOINT_ANGLE().getValue();

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
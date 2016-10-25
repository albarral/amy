/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/ArmBus.h"
#include "amy/arm/config/ArmConfig.h"

namespace amy
{
// Constructor
ArmBus::ArmBus ()
{    
    benabled = false;
    numJoints = 0;
    armName = "arm1";
}

bool ArmBus::addJointBus(std::string jointName)
{  
    JointBus* pBusJoint = 0;
    
    if (jointName.compare(ArmConfig::horizontal_shoulder) == 0)
    {
        pBusJoint = &oBusHS;
    }
    else if (jointName.compare(ArmConfig::vertical_shoulder) == 0)
    {
        pBusJoint = &oBusVS;
    }
    else if (jointName.compare(ArmConfig::elbow) == 0)
    {
        pBusJoint = &oBusEL;
    }
    else if (jointName.compare(ArmConfig::vertical_wrist) == 0)
    {
        pBusJoint = &oBusVW;
    }
    else if (jointName.compare(ArmConfig::horizontal_wrist) == 0)
    {
        pBusJoint = &oBusHW;
    }

    if (pBusJoint != 0)
    {
        // ignore if joint already used
        if (pBusJoint->isEnabled())
            return false;
        
        pBusJoint->init(jointName);
        numJoints++;     
        // arm enabled
        benabled = true;    
        return true;                
    }
    // inexistent joint
    else
        return false;
}

JointBus& ArmBus::getJointBus(std::string jointName)
{
    if (jointName.compare(ArmConfig::horizontal_shoulder) == 0)
    {
        return oBusHS;
    }
    else if (jointName.compare(ArmConfig::vertical_shoulder) == 0)
    {
        return oBusVS;
    }
    else if (jointName.compare(ArmConfig::elbow) == 0)
    {
        return oBusEL;
    }
    else if (jointName.compare(ArmConfig::vertical_wrist) == 0)
    {
        return oBusVW;
    }
    else if (jointName.compare(ArmConfig::horizontal_wrist) == 0)
    {
        return oBusHW;
    }
    
    // if not found return the first joint (should use lists)
    return oBusHS;        
}

std::string ArmBus::toString()
{
    std::string text = "ArmBus:[" + armName + "]\n" +       
         "CO_ARMMOVER_START: " + std::to_string(CO_ARMMOVER_START.getRequested()) + "\n" +
         "CO_ARMMOVER_STOP: " + std::to_string(CO_ARMMOVER_STOP.getRequested()) + "\n" +
         "CO_ARM_PAN: " + std::to_string(CO_ARM_PAN.getRequested()) + " - " + std::to_string(CO_ARM_PAN.getValue()) + "\n" +
         "CO_ARM_TILT: " + std::to_string(CO_ARM_TILT.getRequested()) + " - " + std::to_string(CO_ARM_TILT.getValue()) + "\n" +
         "CO_ARM_RADIUS: " + std::to_string(CO_ARM_RADIUS.getRequested()) + " - " + std::to_string(CO_ARM_RADIUS.getValue()) + "\n" +
//         "SO_ARM_PAN: " + std::to_string(SO_ARM_PAN.getValue()) + "\n" +
//         "SO_ARM_TILT: " + std::to_string(SO_ARM_TILT.getValue()) + "\n" +
//         "SO_ARM_RADIUS: " + std::to_string(SO_ARM_RADIUS.getValue()) + "\n" +
          "\n" + oBusHS.toString() +   
          "\n" + oBusVS.toString() +   
          "\n" + oBusEL.toString() +   
          "\n" + oBusHW.toString() +   
          "\n" + oBusVW.toString();
    
    return text;
}

}

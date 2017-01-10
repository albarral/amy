/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/ArmBus.h"
#include "amy/core/robot/Joint.h"

namespace amy
{
// Constructor
ArmBus::ArmBus ()
{    
    benabled = false;
    numJoints = 0;
    armName = "none";
}

void ArmBus::init(Arm& oArm)
{
    numJoints = 0;
    armName = oArm.getName();
         
    // setup connections for each arm's joint
    std::vector<Joint>& listJoints = oArm.getListJoints();
    for (Joint& oJoint : listJoints)
    {        
        if (addJointBus(oJoint.getName()))
            numJoints++;
    }    
    
    // arm enabled if joints added
    if (numJoints>0)
        benabled = true;
}

bool ArmBus::addJointBus(std::string jointName)
{  
    JointBus* pJointBus = 0;
    
    if (jointName.compare(Arm::horizontal_shoulder) == 0)
    {
        pJointBus = &oBusHS;
    }
    else if (jointName.compare(Arm::vertical_shoulder) == 0)
    {
        pJointBus = &oBusVS;
    }
    else if (jointName.compare(Arm::elbow) == 0)
    {
        pJointBus = &oBusEL;
    }
    else if (jointName.compare(Arm::vertical_wrist) == 0)
    {
        pJointBus = &oBusVW;
    }
    else if (jointName.compare(Arm::horizontal_wrist) == 0)
    {
        pJointBus = &oBusHW;
    }

    // if valid joint, init joint bus
    if (pJointBus != 0)
    {
        pJointBus->init(jointName);
        return true;                
    }
    // else skip
    else
        return false;
}

JointBus& ArmBus::getJointBus(std::string jointName)
{
    if (jointName.compare(Arm::horizontal_shoulder) == 0)
    {
        return oBusHS;
    }
    else if (jointName.compare(Arm::vertical_shoulder) == 0)
    {
        return oBusVS;
    }
    else if (jointName.compare(Arm::elbow) == 0)
    {
        return oBusEL;
    }
    else if (jointName.compare(Arm::vertical_wrist) == 0)
    {
        return oBusVW;
    }
    else if (jointName.compare(Arm::horizontal_wrist) == 0)
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
//          "\n" + oBusHS.toString() +   
//          "\n" + oBusVS.toString() +   
//          "\n" + oBusEL.toString() +   
//          "\n" + oBusHW.toString() +   
//          "\n" + oBusVW.toString() + 
            "\n";
    
    return text;
}

}

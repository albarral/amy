/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/coms/ArmCommander.h"
#include "amy/arm/bus/JointBus.h"

namespace amy
{
ArmCommander::ArmCommander()
{
    bconnected = false;
    pBus = 0;
}

void ArmCommander::connect(ArmBus& oArmBus) 
{
    pBus = &oArmBus;
    bconnected = true;
}

bool ArmCommander::sendCommand(ArmCommand& oArmCommand)
{
    bool bret;
    
    if (!bconnected)
        return false;
    
    // distribute commands to each module sender
    switch (oArmCommand.getBusModule())
    {                
        case ArmCommand::eMOD_MANAGER:
            bret = send2ArmManager(oArmCommand);
            break;
 
        case ArmCommand::eMOD_ARMMOVER:
            bret = send2ArmMover(oArmCommand);
            break;

        case ArmCommand::eMOD_ARMPANNER:
            bret = send2ArmPanner(oArmCommand);
            break;

        case ArmCommand::eMOD_ARMTILTER:
            bret = send2ArmTilter(oArmCommand);
            break;

        case ArmCommand::eMOD_ARMEXTENDER:
            bret = send2ArmExtender(oArmCommand);
            break;

        case ArmCommand::eMOD_JOINTMOVER:
            bret = send2JointMover(oArmCommand);
            break;

        case ArmCommand::eMOD_JOINTCONTROL:
            bret = send2JointControl(oArmCommand);
            break;
    }    
    
    return bret;
}

/*! sends command to the ArmManager */        
bool ArmCommander::send2ArmManager(ArmCommand& oArmCommand)
{
    bool bret = false;
    int busAction = oArmCommand.getBusAction();    

    // finish arm manager
    if (busAction == 0)
    {
        pBus->getCO_FINISH_MANAGER().request();   
        bret = true;        
    }

    return bret;    
}

/*! sends command to ArmMover module */    
bool ArmCommander::send2ArmMover(ArmCommand& oArmCommand)
{
    bool bret = false;
    int busAction = oArmCommand.getBusAction();    

    switch (busAction)
    {        
        // stop ArmMover
        case 0:
            pBus->getCO_ARMMOVER_STOP().request();            
            bret = true;        
            break;
            
        // start ArmMover
        case 1:
            pBus->getCO_ARMMOVER_START().request();            
            bret = true;        
            break;
    }        

    return bret;    
}

/*! sends command to ArmPanner module */    
bool ArmCommander::send2ArmPanner(ArmCommand& oArmCommand)
{
    bool bret = false;
    int angle = (int)oArmCommand.getTargetValue();   

    pBus->getCO_ARM_PAN().request(angle);            
    return true;    
}

/*! sends command to ArmTilter module */    
bool ArmCommander::send2ArmTilter(ArmCommand& oArmCommand)
{
    bool bret = false;
    int angle = (int)oArmCommand.getTargetValue();   

    pBus->getCO_ARM_TILT().request(angle);            
    return true;    
}

/*! sends command to ArmExtender module */    
bool ArmCommander::send2ArmExtender(ArmCommand& oArmCommand)
{
    bool bret = false;
    int radius = (int)oArmCommand.getTargetValue();   

    pBus->getCO_ARM_RADIUS().request(radius);            
    return true;    
}

/*! sends command to JointMover modules */    
bool ArmCommander::send2JointMover(ArmCommand& oArmCommand)
{
    bool bret = false;
    int busAction = oArmCommand.getBusAction();    
    
    // access joint's bus
    JointBus& pJointBus = pBus->getJointBus(oArmCommand.getTargetJoint());   
    pJointBus.getCO_JMOVER_ACTION().request(busAction);   

    return true;    
}

/*! sends command to JointControl modules */    
bool ArmCommander::send2JointControl(ArmCommand& oArmCommand)
{        
    float angle = oArmCommand.getTargetValue();    // the target value is the soll angle
    
    // access joint's bus
    JointBus& pJointBus = pBus->getJointBus(oArmCommand.getTargetJoint());   
    pJointBus.getCO_JOINT_ANGLE().request(angle);       

    return true;    
}

}
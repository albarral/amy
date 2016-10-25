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
}

bool ArmCommander::sendCommand(ArmBus* pBus, ArmCommand& oArmCommand)
{
    bool bret = true;;
        
    // distribute commands to each module sender
    switch (oArmCommand.getBusModule())
    {                
        case ArmCommand::eMOD_MANAGER:
            bret = send2ArmManager(pBus, oArmCommand);
            break;
 
        case ArmCommand::eMOD_ARMMOVER:
            bret = send2ArmMover(pBus, oArmCommand);
            break;

        case ArmCommand::eMOD_ARMPANNER:
            send2ArmPanner(pBus, oArmCommand);
            break;

        case ArmCommand::eMOD_ARMTILTER:
            send2ArmTilter(pBus, oArmCommand);
            break;

        case ArmCommand::eMOD_ARMEXTENDER:
            send2ArmExtender(pBus, oArmCommand);
            break;

        case ArmCommand::eMOD_JOINTMOVER:
            send2JointMover(pBus, oArmCommand);
            break;

        case ArmCommand::eMOD_JOINTCONTROL:
            send2JointControl(pBus, oArmCommand);
            break;
            
        default:
            bret = false;
    }    
    
    return bret;
}

/*! sends command to the ArmManager */        
bool ArmCommander::send2ArmManager(ArmBus* pBus, ArmCommand& oArmCommand)
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
bool ArmCommander::send2ArmMover(ArmBus* pBus, ArmCommand& oArmCommand)
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
void ArmCommander::send2ArmPanner(ArmBus* pBus, ArmCommand& oArmCommand)
{
    int angle = (int)oArmCommand.getTargetValue();   

    pBus->getCO_ARM_PAN().request(angle);            
}

/*! sends command to ArmTilter module */    
void ArmCommander::send2ArmTilter(ArmBus* pBus, ArmCommand& oArmCommand)
{
    int angle = (int)oArmCommand.getTargetValue();   

    pBus->getCO_ARM_TILT().request(angle);            
}

/*! sends command to ArmExtender module */    
void ArmCommander::send2ArmExtender(ArmBus* pBus, ArmCommand& oArmCommand)
{
    int radius = (int)oArmCommand.getTargetValue();   

    pBus->getCO_ARM_RADIUS().request(radius);            
}

/*! sends command to JointMover modules */    
void ArmCommander::send2JointMover(ArmBus* pBus, ArmCommand& oArmCommand)
{
    int busAction = oArmCommand.getBusAction();    
    
    // access joint's bus
    JointBus& pJointBus = pBus->getJointBus(oArmCommand.getTargetJoint());   
    //pJointBus.getCO_JMOVER_ACTION().request(busAction);   
}

/*! sends command to JointControl modules */    
void ArmCommander::send2JointControl(ArmBus* pBus, ArmCommand& oArmCommand)
{        
    float angle = oArmCommand.getTargetValue();    // the target value is the soll angle
    
    // access joint's bus
    JointBus& pJointBus = pBus->getJointBus(oArmCommand.getTargetJoint());   
    pJointBus.getCO_JOINT_ANGLE().request(angle);       
}

}
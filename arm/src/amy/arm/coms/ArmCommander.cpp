/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/arm/coms/ArmCommander.h"

namespace amy
{
ArmCommander::ArmCommander()
{
    bconnected = false;
    pBus = 0;
    pBusHShoulder = 0;
    pBusVShoulder = 0;
    pBusElbow = 0;
    pBusVWrist = 0;
}

void ArmCommander::connect(ArmBus& oArmBus) 
{
    pBus = &oArmBus;
    pBusHShoulder = &pBus->getBusHS();
    pBusVShoulder = &pBus->getBusVS();
    pBusElbow = &pBus->getBusEL();
    pBusVWrist = &pBus->getBusVW();
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

/*! sends command to JointMover modules */    
bool ArmCommander::send2JointMover(ArmCommand& oArmCommand)
{
    bool bret = false;
    int targetJoint = oArmCommand.getTargetJoint();    
    int busAction = oArmCommand.getBusAction();    
    
    switch (targetJoint)
    {        
        case ArmCommand::eJOINT_HSHOULDER:
            if (pBusHShoulder > 0)
            {
                pBusHShoulder->getCO_JMOVER_ACTION().request(busAction);            
                bret = true;                        
            }
            break;
                        
        case ArmCommand::eJOINT_VSHOULDER:
            if (pBusVShoulder > 0)
            {
                pBusVShoulder->getCO_JMOVER_ACTION().request(busAction);            
                bret = true;                        
            }
            break;

        case ArmCommand::eJOINT_ELBOW:
            if (pBusElbow > 0)
            {
                pBusElbow->getCO_JMOVER_ACTION().request(busAction);            
                bret = true;                        
            }
            break;
            
        case ArmCommand::eJOINT_VWRIST:
            if (pBusVWrist > 0)
            {
                pBusVWrist->getCO_JMOVER_ACTION().request(busAction);            
                bret = true;                        
            }
            break;
    }    

    return bret;    
}

/*! sends command to JointControl modules */    
bool ArmCommander::send2JointControl(ArmCommand& oArmCommand)
{        
    bool bret = false;
    int targetJoint = oArmCommand.getTargetJoint();    
    float angle = oArmCommand.getTargetValue();    // the target value is the soll angle
    
    switch (targetJoint)
    {        
        case ArmCommand::eJOINT_HSHOULDER:
            if (pBusHShoulder > 0)
            {
                pBusHShoulder->getCO_JOINT_ANGLE().request(angle);       
                bret = true;                        
            }
            break;
                        
        case ArmCommand::eJOINT_VSHOULDER:
            if (pBusVShoulder > 0)
            {
                pBusVShoulder->getCO_JOINT_ANGLE().request(angle);    
                bret = true;                        
            }
            break;

        case ArmCommand::eJOINT_ELBOW:
            if (pBusElbow > 0)
            {
                pBusElbow->getCO_JOINT_ANGLE().request(angle);          
                bret = true;                        
            }
            break;
            
        case ArmCommand::eJOINT_VWRIST:
            if (pBusVWrist > 0)
            {
                pBusVWrist->getCO_JOINT_ANGLE().request(angle);
                bret = true;                        
            }
            break;
    }    

    return bret;    
}

}
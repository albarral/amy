/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/arm/coms/ArmCommand.h"
#include "amy/arm/modules/JointMover.h"

namespace amy
{

ArmCommand::ArmCommand()
{
    resetCommand();
}

/*! resets arm command values */
void ArmCommand::resetCommand()
{
    targetAction = eACT_UNDEFINED;    
    targetJoint = eJOINT_UNDEFINED;
    targetValue = 0;
    busModule = eMOD_UNDEFINED;
}

bool ArmCommand::setTargetAction(int action) 
{
    // store action if valid
    if (action > eACT_UNDEFINED && action < eACT_DIM)
    {
        targetAction = action;
        return true;
    }
    // otherwise set it undefined
    else 
    {
        targetAction = eACT_UNDEFINED;
        return false;        
    }
}


/*! builds a proper control command to be sent though the bus */
bool ArmCommand::buildBusCommand()
{
    // skip if joint action but undefined joint
    bool bret = true;
    switch (targetAction)
    {
        case eACT_ARM_END:
                setBusModule(eMOD_MANAGER);
                setBusAction(0);
                break;
                
        case eACT_ARM_STOP:
            // ... all joints stop ???
            break;
        
        case eACT_MOVEMENT_START:
                setBusModule(eMOD_ARMMOVER);
                setBusAction(1);
            break;
            
        case eACT_MOVEMENT_STOP:
                setBusModule(eMOD_ARMMOVER);
                setBusAction(0);
            break;
            
        case eACT_SET_PAN:
                setBusModule(ArmCommand::eMOD_ARMPANNER);
                setBusAction(targetValue);
            break;
            
        case eACT_SET_TILT:
                setBusModule(ArmCommand::eMOD_ARMTILTER);
                setBusAction(targetValue);
            break;

        case eACT_SET_EXTENSION:
                setBusModule(ArmCommand::eMOD_ARMEXTENDER);
                setBusAction(targetValue);
            break;
            
        case eACT_JOINT_BRAKE:
//                setBusModule(eMOD_JOINTMOVER);
//                setBusAction(JointMover::eMOV_BRAKE);
            break;
            
        case eACT_JOINT_STOP:
//                setBusModule(eMOD_JOINTMOVER);
//                setBusAction(JointMover::eMOV_STOP);
            break;

        case eACT_JOINT_ANGLE:
            setBusModule(ArmCommand::eMOD_JOINTCONTROL);
            setBusAction(targetValue);
        break;
                
        // any other action is invalid
        default:
            bret = false;
    }
    
    return bret;
}

bool ArmCommand::isJointAction(int action)
{
    bool bjoint = false;
    
    switch (action)
    {
        case eACT_SET_PAN:
        case eACT_SET_TILT:
        case eACT_SET_EXTENSION:
        case eACT_JOINT_BRAKE:
        case eACT_JOINT_STOP:
        case eACT_JOINT_ANGLE:
            bjoint = true;
            break;
    }
    return bjoint;
}


}
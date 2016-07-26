/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/bus/ArmBus.h"

namespace amy
{
// Constructor
ArmBus::ArmBus ()
{    
    benabled = false;
    numJoints = 0;
}

bool ArmBus::add4Joint(std::string jointName)
{
    // ignore if joint already used
    if (checkExistingJoint(jointName))
        return false;

    if (numJoints < SAM_MAX_JOINTS)
    {
        oJointBus[numJoints].init(jointName);
        numJoints++;        
        benabled = true;    
        return true;
    }    
    else
        return false;
}

JointBus& ArmBus::getJointBus(std::string jointName)
{
    for (int i=0; i<numJoints; i++)
    {
        if (oJointBus[i].getJointName().compare(jointName) == 0)
            return oJointBus[i];
    }
    
    // if not found return the first joint (should use lists)
    return oJointBus[0];        
}

JointBus& ArmBus::getJointBusByIndex(int index)
{
    if (index < SAM_MAX_JOINTS)
        return oJointBus[index];
    
    // if not found return the first joint (should use lists)
    return oJointBus[0];        
}

bool ArmBus::checkExistingJoint(std::string jointName)
{
    for (int i=0; i<SAM_MAX_JOINTS; i++)
    {
        if (oJointBus[i].getJointName().compare(jointName) == 0)
            return true;
    }
    
    return false;        
}

}

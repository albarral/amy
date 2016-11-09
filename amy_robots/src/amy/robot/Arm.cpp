/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "amy/robot/Arm.h"

namespace amy
{
const std::string Arm::horizontal_shoulder = "hs";
const std::string Arm::vertical_shoulder = "vs";
const std::string Arm::elbow = "el";
const std::string Arm::horizontal_wrist = "hw";
const std::string Arm::vertical_wrist = "vw";

Arm::Arm ()
{
    name = "arm";
    type = Arm::eUNDEF_ARM;
    lenHumerus = 0;     
    lenRadius = 0;
}

Arm::~Arm()
{
    reset();
}

void Arm::reset()
{
    listJoints.clear();    
}

void Arm::addJoint(Joint& oJoint)
{
    listJoints.push_back(oJoint);    
}

bool Arm::hasJoint(std::string jointName)
{
    bool bfound = false;
    
    for (Joint& oJoint: listJoints)
    {
        if (oJoint.getName().compare(jointName) == 0)
        {
            bfound = true;
            break;
        }
    }    
    return bfound;
}

Joint* Arm::getJointByPos(int pos)
{    
    Joint* pJoint = 0;

    if (pos < listJoints.size())
        pJoint = &(listJoints.at(pos));

    return pJoint;
}

Joint* Arm::getJointByName(std::string jointName)
{
    Joint* pJoint = 0;
    
    for (Joint& oJoint: listJoints)
    {
        if (oJoint.getName().compare(jointName) == 0)
        {
            pJoint = &(oJoint);
            break;
        }
    }    

    return pJoint;
}

}

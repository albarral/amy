/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "amy/core/robot/Arm.h"

namespace amy
{
const std::string Arm::pan = "pan";
const std::string Arm::tilt = "tilt";
const std::string Arm::radial = "radial";

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

bool Arm::hasJoint(int jointType)
{
    bool bfound = false;
    
    for (Joint& oJoint: listJoints)
    {
        if (oJoint.getType() == jointType)
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

Joint* Arm::getJointByType(int jointType)
{
    Joint* pJoint = 0;
    
    for (Joint& oJoint: listJoints)
    {
        if (oJoint.getType() == jointType)
        {
            pJoint = &(oJoint);
            break;
        }
    }    

    return pJoint;
}

bool Arm::isValidAxis(int value)
{
    return (value >= 0 && value < Arm::eAXIS_DIM);
}

std::string Arm::getName4Axis(int axis)
{
    switch (axis)
    {
        case Arm::eAXIS_PAN:
            return Arm::pan;
            break;
        case Arm::eAXIS_TILT:
            return Arm::tilt;
            break;
        case Arm::eAXIS_RADIAL:
            return Arm::radial;
            break;
        default:
            return "";
    }
}

std::string Arm::toString()
{
    std::string desc = "Arm [name=" + name + ", type=" + std::to_string(type) + ", lenHum=" + std::to_string(lenHumerus) + " lenRadius=" + std::to_string(lenRadius);
    // describe joints
    for (Joint& oJoint: listJoints)
    {
        desc += "\n" + oJoint.toString();
    }    
    desc += "]";
    return desc;
}

}

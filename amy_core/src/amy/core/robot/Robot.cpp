/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <stddef.h>

#include "amy/core/robot/Robot.h"

namespace amy
{    
Robot::Robot ()
{
    name = "robot";
}

Robot::~Robot()
{
    reset();
}

void Robot::reset()
{
    listArms.clear();    
}

void Robot::addArm(Arm& oArm)
{
    listArms.push_back(oArm);    
}

bool Robot::hasArmType(int type)
{
    bool bfound = false;
    
    for (Arm& oArm: listArms)
    {
        if (oArm.getType() == type)
        {
            bfound = true;
            break;
        }
    }    
    return bfound;
}

Arm* Robot::getArmByType(int type)
{
    Arm* pArm = 0;
    
    for (Arm& oArm: listArms)
    {
        if (oArm.getType() == type)
        {
            pArm = &(oArm);
            break;
        }
    }    

    return pArm;
}

}

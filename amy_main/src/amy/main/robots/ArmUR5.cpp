/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/main/robots/ArmUR5.h"
#include "amy/core/robot/Joint.h"

namespace amy
{
// Constructor
ArmUR5::ArmUR5 ()
{
    setName("UR5-arm");
        
    Joint oJoint; 

    // horizontal shoulder - frontal arm = 0
    oJoint.setType(Joint::eJOINT_HS);
    oJoint.setLimits(-90, 90);
    addJoint(oJoint);

    // vertical shoulder - horizontal arm = 0
    oJoint.setType(Joint::eJOINT_VS);
    oJoint.setLimits(0, 135);
    addJoint(oJoint);

    // elbow -  straight arm = 0
    oJoint.setType(Joint::eJOINT_ELB);
    oJoint.setLimits(-150, 150);
    addJoint(oJoint);

    // NO horizontal wrist
    
    // vertical wrist - straight hand = 90
    oJoint.setType(Joint::eJOINT_VW);
    oJoint.setLimits(180, 360);
    addJoint(oJoint);
        
    lenHumerus = 40;   // cm    
    lenRadius = 40;  // cm
}
}


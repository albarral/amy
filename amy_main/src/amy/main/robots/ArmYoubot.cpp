/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/main/robots/ArmYoubot.h"
#include "amy/core/robot/Joint.h"

namespace amy
{
// Constructor
ArmYoubot::ArmYoubot ()
{    
    setName("Youbot-arm");
        
    Joint oJoint; 

    // horizontal shoulder - frontal arm ?
    oJoint.setType(Joint::eJOINT_HS);
    oJoint.setLimits(0, 90);
    addJoint(oJoint);

    // vertical shoulder - horizontal arm ?
    oJoint.setType(Joint::eJOINT_VS);
    oJoint.setLimits(-30, 160);
    addJoint(oJoint);

    // elbow -  straight arm ?
    oJoint.setType(Joint::eJOINT_ELB);
    oJoint.setLimits(-240, -60);
    addJoint(oJoint);

    // NO horizontal wrist
    
    // vertical wrist - straight hand ?
    oJoint.setType(Joint::eJOINT_VW);
    oJoint.setLimits(0, 180);
    addJoint(oJoint);
        
    lenHumerus = 20;
    lenRadius = 20;
}
}

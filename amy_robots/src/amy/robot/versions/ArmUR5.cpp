/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/robot/versions/ArmUR5.h"

namespace amy
{
// Constructor
ArmUR5::ArmUR5 ()
{
    setName("UR5-arm");
        
    Joint oJoint; 

    // horizontal shoulder - frontal arm = 0
    oJoint.setName(Arm::horizontal_shoulder);
    oJoint.setLimits(-90, 90);
    addJoint(oJoint);

    // vertical shoulder - horizontal arm = 0
    oJoint.setName(Arm::vertical_shoulder);
    oJoint.setLimits(0, 135);
    addJoint(oJoint);

    // elbow -  straight arm = 0
    oJoint.setName(Arm::elbow);
    oJoint.setLimits(-150, 150);
    addJoint(oJoint);

    // NO horizontal wrist
    
    // vertical wrist - straight hand = 90
    oJoint.setName(Arm::vertical_wrist);
    oJoint.setLimits(180, 360);
    addJoint(oJoint);
        
    lenHumerus = 40;   // cm    
    lenRadius = 40;  // cm
}
}


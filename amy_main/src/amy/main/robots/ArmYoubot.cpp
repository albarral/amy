/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/main/robots/ArmYoubot.h"

namespace amy
{
// Constructor
ArmYoubot::ArmYoubot ()
{    
    setName("Youbot-arm");
        
    Joint oJoint; 

    // horizontal shoulder - frontal arm ?
    oJoint.setName(Arm::horizontal_shoulder);
    oJoint.setLimits(0, 90);
    addJoint(oJoint);

    // vertical shoulder - horizontal arm ?
    oJoint.setName(Arm::vertical_shoulder);
    oJoint.setLimits(-30, 160);
    addJoint(oJoint);

    // elbow -  straight arm ?
    oJoint.setName(Arm::elbow);
    oJoint.setLimits(-240, -60);
    addJoint(oJoint);

    // NO horizontal wrist
    
    // vertical wrist - straight hand ?
    oJoint.setName(Arm::vertical_wrist);
    oJoint.setLimits(0, 180);
    addJoint(oJoint);
        
    lenHumerus = 20;
    lenRadius = 20;
}
}


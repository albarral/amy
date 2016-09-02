/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/config/versions/ArmUR5.h"

namespace amy
{
// Constructor
ArmUR5::ArmUR5 ()
{    
        robotName = "UR5";
        numJoints = 4;
        
        // horizontal shoulder - frontal arm = 0
        bHS = true;
        lowerHS = -90;
        upperHS = 90;
        // vertical shoulder - horizontal arm = 0
        bVS = true;  
        lowerVS = 0;  
        upperVS = 135;
        // elbow -  straight arm = 0
        bEL = true;        
        lowerEL = -90; 
        upperEL = 90; 
        // NO horizontal wrist
        bHW = false;  
        // vertical wrist - straight hand = 90
        bVW = true;    
        lowerVW = 180;  
        upperVW = 360;
        
        len = 20;
}
}


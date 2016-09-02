/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/config/versions/ArmYoubot.h"

namespace amy
{
// Constructor
ArmYoubot::ArmYoubot ()
{    
        robotName = "Youbot";
        numJoints = 4;
        
        // horizontal shoulder - frontal arm = ?
        bHS = true;
        lowerHS = 0;
        upperHS = 90;
        // vertical shoulder - horizontal arm = ?
        bVS = true;  
        lowerVS = -30;  
        upperVS = 160;
        // elbow -  straight arm = ?
        bEL = true;        
        lowerEL = -240; 
        upperEL = -60; 
        // NO horizontal wrist
        bHW = false;  
        // vertical wrist - straight hand = ?
        bVW = true;    
        lowerVW = 0;  
        upperVW = 180;
        
        len = 20;
}
}


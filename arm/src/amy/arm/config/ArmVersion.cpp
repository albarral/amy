/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/config/ArmVersion.h"

namespace amy
{
// Constructor
ArmVersion::ArmVersion ()
{    
        robotName = "default";
        numJoints = 4;
        
        // horizontal shoulder 
        bHS = true;
        lowerHS = -60;
        upperHS = 60;
        // vertical shoulder 
        bVS = true;  
        lowerVS = 0;  
        upperVS = 90;
        // elbow
        bEL = true;        
        lowerEL = -45; 
        upperEL = 45; 
        // horizontal wrist
        bHW = false;  
        lowerHW = 0;
        upperHW = 0;
        // vertical wrist
        bVW = true;    
        lowerVW = 0;  
        upperVW = 180;
        
        lenHumerus = 20;
}
}


#ifndef __AMY_MOVE_RADIALDRIVER_H
#define __AMY_MOVE_RADIALDRIVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/move/JointDriver.h"
#include "amy/move/ArmMath.h"

namespace amy
{
// Class used to move an arm to a target radial position by means of acceleration commands. Designed for the elbow joint.
// An extension of RadialDriver class.
// Two extra things need to be set:
// - the arm segments sizes (to convert radius to angles)
// - the desired work plane (up or down, as same radius can be achieved with two angles)
// Usage:    
// Initialize as a normal RadialDriver (sensitivity and tolerance) 
// Set arm segments and work plane
// Then work as normal RadialDriver (request target and call drive repeatedly till movement finished)     
class RadialDriver : public JointDriver
{
private:
    // request
    float targetRadius;          // requested joint position
    // control 
    ArmMath oArmMath;       // class for arm computations
    int workSign;                 // sign of target angles (defines the working plane)  

public:
        RadialDriver();
        //~RadialDriver();
                
       // sets sizes of arm segments 
       void setArmSize(int lenHumerus, int lenRadius);               
       // sets elbow to work upside (with positive elbow angles)
       void workUp();
       // sets elbow to work downside (with negative elbow angles)
       void workDown();

       // sets the target position
        void setTargetRadius(float radius);
                      
//        virtual std::string toString();
//        virtual std::string paramsToString();
        
};
}
#endif

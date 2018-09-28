#ifndef __AMY_ARM_RADIALCONTROL_H
#define __AMY_ARM_RADIALCONTROL_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/arm/move/JointControl.h"
#include "tron/math/ArmMath.h"

namespace amy
{
// Class used to move an arm to a target radial position by means of acceleration commands. Designed for the elbow joint.
// An extension of RadialControl class.
// Two extra things need to be set:
// - the arm segments sizes (to convert radius to angles)
// - the desired work plane (up or down, as same radius can be achieved with two angles)
// Usage:    
// Initialize as a normal RadialControl (sensitivity and tolerance) 
// Set arm segments and work plane
// Then work as normal RadialControl (request target and call drive repeatedly till movement finished)     
class RadialControl : public JointControl
{
private:
    // request
    float targetRadius;          // requested joint position
    // control 
    tron::ArmMath oArmMath;       // class for arm computations
    int workSign;                 // sign of target angles (defines the working plane)  

public:
        RadialControl(int lenHumerus, int lenRadius);
        //~RadialControl();
                
       // sets elbow to work upside (with positive elbow angles)
       void workUp();
       // sets elbow to work downside (with negative elbow angles)
       void workDown();

       // new radial move requested (to target radius)
        virtual void newMove(float radius) override;
                      
        virtual std::string toString() override;
        virtual std::string paramsToString() override;
        
};
}
#endif

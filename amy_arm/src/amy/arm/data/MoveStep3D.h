#ifndef __AMY_MOVE_STEP3D_H
#define __AMY_MOVE_STEP3D_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/data/MoveStep.h"

namespace amy
{
// Extension of MoveStep class for 3D movements
// Besides to the inherited MoveStep parameters, the 3D move incorporates:
// - a depth direction -> given by an angle
// - a depth speed (reached after acceleration) 
class MoveStep3D : public MoveStep
{   
private:
    int zangle;    // movement direction along z axis (degrees)
    // logic
    int zmove;     // JointMover commands for depth movement 
    float vz;  // cruise speed for depth movement 

public:    
    MoveStep3D();
//    MoveStep3D(int xyangle, int zangle, int tics, int maxSpeed);
//    ~MoveStep3D();

    void setZangle(int value) {zangle = value;};    
    int getZangle() {return zangle;}
    
    int getZmove() {return zmove;}
    int getZspeed() {return vz;}

    // computation of JointMover commands & cruise speeds
    //virtual void compute();   
    virtual bool is3D() {return true;};
};
}
#endif

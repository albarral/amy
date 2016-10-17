/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include <vector>

#include "amy/arm/modules/ArmComputer.h"
#include "amy/arm/modules/JointMover.h"

#define PI 3.14159265


namespace amy
{
// computes all the move steps in a movement
void ArmComputer::computeMovement(Movement& oMovement)
{
    std::vector<MoveStep>& listMoveSteps = oMovement.getListMoveSteps();
    
    for (MoveStep& oMoveStep : listMoveSteps)
    {
        if (!oMoveStep.isStepEnding())
            computeMoveStep(oMoveStep);
    }
    
    oMovement.setComputed(true);
}

// Computation of the proper joint speeds & commands.
// Core: tg(angle) = Vy / Vx
// First, the speeds relation is obtained (from the angle).
// Then, speeds are normalized to the maxSpeed.
void ArmComputer::computeMoveStep(MoveStep& oMoveStep)
{
    int xsign, ysign;
    int angle = oMoveStep.getAngle();
    int vmax = oMoveStep.getMaxSpeed();
    float vx;  // cruise speed for horizontal movement 
    float vy;  // cruise speed for vertical movement 

    // sign of x movement
    if (angle > 90 && angle < 270)
        xsign = -1;
    else 
        xsign = 1;
    
    // sign of y movement
    if (angle > 0 && angle < 180)
        ysign = 1;
    else 
        ysign = -1;

    // pure up move (tangent singularity)
    if (angle == 90)
    {
        vx = 0;
        vy = vmax;
    }
    // pure down move (tangent singularity) 
    else if (angle == 270)
    {
        vx = 0;
        vy = -vmax;
    }
    // rest of angles
    else
    {
        // obtain relation = vy / vx
        float relation = tan((float)angle * PI / 180.0); 
        
        // if x speed larger, maximize it & normalize y speed
        if (fabs(relation) <= 1.0)
        {
            vx = xsign*vmax;
            vy = vx*relation;            
        }
        // if y speed larger, maximize it & normalize x speed
        else
        {
            vy = ysign*vmax;
            vx = vy/relation;       // relation here is > 1     
        }                        
    }
    
    // transform speed to JointMover commands
    oMoveStep.setXmove(fromSpeed2JointCommand(vx));
    oMoveStep.setYmove(fromSpeed2JointCommand(vy));
    oMoveStep.setXspeed(vx);
    oMoveStep.setYspeed(vy);
    oMoveStep.setComputed(true);
};


// get the proper joint command to reach the specified joint speed
// used int to avoid triggering movements for |speeds| < 1.0
int ArmComputer::fromSpeed2JointCommand(int v)
{
    if (v > 0) 
        return JointMover::eMOV_PUSH_FRONT;
    else if (v < 0)
        return JointMover::eMOV_PUSH_BACK;
    else
        return 99; //JointMover::eMOV_STOP;
};


}

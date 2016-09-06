#ifndef __AMY_ARM_ARMCOMPUTER_H
#define __AMY_ARM_ARMCOMPUTER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/data/Movement.h"
#include "amy/arm/data/MoveStep.h"

namespace amy
{
// Class used to compute required JointMover commands & cruise speeds needed to perform specific move steps.
// This move steps (2D) are defined by a direction angle and a desired speed.
    
class ArmComputer
{
public:    
   // computes required JointMover commands for the given movement
   static void computeMovement(Movement& oMovement);
   // computes required JointMover commands for the given move step 
   static void computeMoveStep(MoveStep& oMoveStep);
    
private:
    // get the proper joint command to reach the specified joint speed
    static int fromSpeed2JointCommand(int v);
};
}
#endif

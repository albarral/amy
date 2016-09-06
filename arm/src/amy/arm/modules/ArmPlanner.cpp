/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/ArmPlanner.h"
#include "amy/arm/modules/JointMover.h"
#include "amy/arm/data/MoveStep.h"


namespace amy
{
// computes all the move steps in a movement
void ArmPlanner::buildPajaritaMovement(Movement& oMovement)
{
    int maxSpeed = 40;    
  
    oMovement.reset();
    oMovement.setMaxSpeed(maxSpeed);

    // step1: move right for 1000 tics
    MoveStep oStep1(45, 5000, maxSpeed);
    oMovement.addMoveStep(oStep1);
    // brake
    oStep1.setStepEnding(JointMover::eMOV_BRAKE);
    oMovement.addMoveStep(oStep1);

    // step2: move left for 1000 tics
    MoveStep oStep2(135, 2000, maxSpeed);
    oMovement.addMoveStep(oStep2);
    // brake
    oStep2.setStepEnding(JointMover::eMOV_BRAKE);
    oMovement.addMoveStep(oStep2);
   
    MoveStep oStep3(210, 5000, maxSpeed);
    oMovement.addMoveStep(oStep3);
    // brake
    oStep3.setStepEnding(JointMover::eMOV_BRAKE);
    oMovement.addMoveStep(oStep3);

    MoveStep oStep4(315, 5000, maxSpeed);
    oMovement.addMoveStep(oStep4);
    // brake
    oStep4.setStepEnding(JointMover::eMOV_BRAKE);
    oMovement.addMoveStep(oStep4);
}

}

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/ArmPlanner.h"
//#include "amy/arm/modules/JointMove.h"
#include "amy/arm/data/MoveStep.h"


namespace amy
{
// computes all the move steps in a movement
void ArmPlanner::buildPajaritaMovement(Movement& oMovement)
{
    int maxSpeed = 10;    
    
    int angle = 45;
    int tics = 2000;
    int endings = 99; //JointMove::eMOV_STOP;

    oMovement.reset();
    oMovement.setMaxSpeed(maxSpeed);

    // arm positioning
    MoveStep oStep0(0, 1000, maxSpeed);    
    oMovement.addMoveStep(oStep0);
    // brake
    oStep0.setStepEnding(endings);
    oMovement.addMoveStep(oStep0);

    // step1: up
    MoveStep oStep1(90, tics, maxSpeed);
    oMovement.addMoveStep(oStep1);
    // brake
    oStep1.setStepEnding(endings);
    oMovement.addMoveStep(oStep1);

    // step2: down-left
    MoveStep oStep2(180+angle, 2*tics, maxSpeed);
    oMovement.addMoveStep(oStep2);
    // brake
    oStep2.setStepEnding(endings);
    oMovement.addMoveStep(oStep2);
   
    // step3: up
    MoveStep oStep3(90, tics, maxSpeed);
    oMovement.addMoveStep(oStep3);
    // brake
    oStep3.setStepEnding(endings);
    oMovement.addMoveStep(oStep3);

    // step4: down right
    MoveStep oStep4(360-angle, 2*tics, maxSpeed);
    oMovement.addMoveStep(oStep4);
    // brake
    oStep4.setStepEnding(endings);
    oMovement.addMoveStep(oStep4);
}

}

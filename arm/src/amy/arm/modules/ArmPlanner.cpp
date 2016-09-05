/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/modules/ArmPlanner.h"
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
    MoveStep oStep1(180, 5000, maxSpeed);
    oMovement.addMoveStep(oStep1);

    // step2: move left for 1000 tics
    //MoveStep oStep2(180, 1000, maxSpeed);
    //oMovement.addMoveStep(oStep2);
   
    // more steps to complete pajarita ...           
}

}

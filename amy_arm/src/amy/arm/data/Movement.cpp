/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/data/Movement.h"

namespace amy
{
Movement::Movement ()
{
    ID = 0;
    name = "";
    vmax = 0;
}

Movement::~Movement()
{
    reset();
}

void Movement::reset()
{
    listMoveSteps.clear();    
}

void Movement::addMoveStep(MoveStep& oMoveStep)
{
    listMoveSteps.push_back(oMoveStep);    
}
    
// updates all movement steps with the movement max speed (they'll need recomputation)
void Movement::propagateSpeed2Steps()
{
    for (MoveStep& oMoveStep : listMoveSteps)
    {
        oMoveStep.setMaxSpeed(vmax);
        oMoveStep.setComputed(false);
    }
    
    setComputed(false);
}


}

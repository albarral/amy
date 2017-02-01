/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/MoveState.h"

namespace amy
{
MoveState::MoveState ()
{
    state = eMOVE_DONE;
}

void MoveState::moveRequested()
{
    state = eMOVE_REQUESTED;
}

void MoveState::moveGoing()
{
    state = eMOVE_GOING;
}

void MoveState::moveBlocked()
{
    state = eMOVE_BLOCKED;
}

void MoveState::moveDone()
{
    state = eMOVE_DONE;    
}

}

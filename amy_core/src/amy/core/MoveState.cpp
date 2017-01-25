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
    state = eMOVE_NEW;
}

void MoveState::moveDoing()
{
    state = eMOVE_DOING;
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

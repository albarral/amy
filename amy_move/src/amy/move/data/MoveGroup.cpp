/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/move/data/MoveGroup.h"

namespace amy
{
MoveGroup::MoveGroup ()
{
    name = "";
    intensity = 0.0;
}

MoveGroup::~MoveGroup()
{
    reset();
}

void MoveGroup::reset()
{
    listMovements.clear();    
}

void MoveGroup::updateIntensity(float value)
{
    intensity = value;
    compute();    
}

void MoveGroup::addMovement(Movement& oMovement)
{
    listMovements.push_back(oMovement);    
}
    
// updates all movements in the list with the given intensity
void MoveGroup::compute()
{
    for (Movement& oMovement : listMovements)
    {
        // movements are recomputed automatically on intensity changes
        oMovement.updateIntensity(intensity);
    }
}


}

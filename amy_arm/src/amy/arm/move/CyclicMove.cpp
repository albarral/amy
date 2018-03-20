/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/move/CyclicMove.h"

namespace amy
{
                    
// get maximum triangular speed needed to achieve a cyclic movement of given amplitude and frequency
float CyclicMove::getTriangularSpeed4Movement(float freq, float amp)
{
    // on each period the amplitude must be walked twice
    float avgSpeed = 2.0*amp*freq;    
    // in a triangular signal the top value is twice the average value
    return 2.0*avgSpeed;
}
}
/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/math/CyclicMove.h"
#include "amy/math/Angle.h"

namespace amy
{
CyclicMove::CyclicMove()
{
    bsimple = true;
    freq1 = 0.0;
    angle1 = 0.0;
    amp1 = 0.0;
    freq2 = 0.0;
    angle2 = 0.0;
    amp2 = 0.0;
}

void CyclicMove::makeWider(float change)
{
    // just affects first component
    amp1 = change*amp1;    
}

void CyclicMove::makeTaller(float change)
{
    // just affects second component
    amp2 = change*amp2;    
}

void CyclicMove::makeFaster(float change)
{
    // affects both components equally
    freq1 = change*freq1;
    freq2 = change*freq2;
}

void CyclicMove::makeTurn(float degrees)
{
    // affects both components equally
    angle1 += degrees;
    angle2 += degrees;
    // keep angles inside limits [0, 360)
    angle1 = Angle::inLimits(angle1);
    angle2 = Angle::inLimits(angle2);    
}

}

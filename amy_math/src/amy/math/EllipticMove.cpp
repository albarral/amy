/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/math/EllipticMove.h"
#include "amy/math/MathDefines.h"

namespace amy
{
EllipticMove::EllipticMove()
{
    angle = 0.0;
    lenA = lenB = 0;
    freq = 0.0;    
    reset();
}

void EllipticMove::reset()
{
    bDual = false;
    vx1 = vy1 = vx2 = vy2 = 0.0;    
    ax1 = ay1 = ax2 = ay2 = 0.0;    
}

void EllipticMove::compute()
{
    // vx1 = vA cos(a);     vy1 = vA sin(a);
    // vx2 = -vB sin(a);    vy2 = vB cos(a);
    // ax1 = 8f vx1;         ay1 = 8f vy1
    // ax2 = 8f vx2;         ay2 = 8f vy2
    
    // just compute for valid frequencies
    if (freq > 0.0)
    {
        // check dual movement
        bDual = (lenB != 0.0);

        // convert to radians
        float radians = angle * KPI_DIV_180;
        float sinA = sin(radians);
        float cosA = cos(radians);
        float factor = 8.0*freq;

        // compute first linear movement
        float vA = 2.0*lenA*freq;
        vx1 = vA*cosA;
        vy1 = vA*sinA;  
        ax1 = factor*vx1;
        ay1 = factor*vy1;
        
        // if dual movement
        if (bDual)
        {
            // compute second linear movement
            float vB = 2.0*lenB*freq;
            vx2 = -vB*sinA;
            vy2 = vB*cosA;              
            ax2 = factor*vx2;
            ay2 = factor*vy2;
        }
        // otherwise, clear second linear movement
        else
        {
            vx2 = vy2 = 0.0;    
            ax2 = ay2 = 0.0;                
        }
    }
    // if null frequency, reset
    else
        reset();    
}

std::string EllipticMove::toString()
{
    return "EllipticMove: [angle=" + std::to_string(angle) +
            ", mayor=" + std::to_string(lenA) + 
            ", minor=" + std::to_string(lenB) +
            ", freq=" + std::to_string(freq) + "]";
}
}

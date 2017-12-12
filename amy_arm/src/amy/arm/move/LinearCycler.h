#ifndef __AMY_MOVE_LINEARCYCLER_H
#define __AMY_MOVE_LINEARCYCLER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "maty/math/Clock.h"
#include "maty/math/TriangularSignal.h"
#include "maty/math/Vector.h"

namespace amy
{
// Class used to perform cyclic linear movements.
// The class inputs are: the frequency, the movement amplitude and the orientation angle.
// A triangular signal is used to generate the cyclic movements.
// The output is a speed vector.
class LinearCycler
{
private:
    float freq;             // movement frequency (Hz))
    float angle;             // movement frequency (Hz))
    float amplitude;     // movement amplitude (degrees)
    float movSpeed;     // max speed for the movement (depends on amplitude & frequency)
    maty::TriangularSignal oTriangularSignal;     // triangular signal used to achieve cyclic output
    // output
    maty::Vector oSpeedVector;
    
public:
    LinearCycler();
    //~LinearCycler();                

    void setFreq(float value);
    void setAngle(float value);
    void setAmp(float value);
    float getFreq() {return freq;}; 
    float getAngle() {return angle;}; 
    float getAmp() {return amplitude;}; 

    // trigger the movement
    void trigger(maty::Clock& oClock);
    // update the movement (perform it)
    void update(maty::Clock& oClock);
    // get movement xy speeds
    float getXSpeed() {return oSpeedVector.getXComponent();}; 
    float getYSpeed() {return oSpeedVector.getYComponent();}; 
    // get movement phase
    int getPhase();
    // get description
    std::string toString();
private:    
    // define movement's max speed
    void redefine();
};
}
#endif

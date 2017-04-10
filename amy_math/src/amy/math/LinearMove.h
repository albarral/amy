#ifndef __AMY_MATH_LINEARMOVE_H
#define __AMY_MATH_LINEARMOVE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
 
namespace amy
{
// Class used to compute the speed components (vx, vy) of a linear movement of given absolute speed and fixed angle.
class LinearMove
{
private:
    float angle;  // movement frontal angle (degrees))
    float cosA;   // cosinus(angle)
    float sinA;   // sinus(angle)
    // output
    float vx;   // x speed of movement (deg/s)
    float vy;   // y speed of movement (deg/s)
    
public:  
    LinearMove();
    //~LinearMove();

    // parameters
    void setAngle(float value);
    // compute speed components of the given speed value (at the movement's angle)
    void compute(float speed);

    // speed vector components
    float getXSpeed() {return vx;}; 
    float getYpeed() {return vy;}; 
};
}
#endif

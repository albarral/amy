#ifndef __AMY_MATH_ELLIPTICMOVE_H
#define __AMY_MATH_ELLIPTICMOVE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
 
namespace amy
{
// Class used to compute how to perform an elliptic movement.
// Elliptic movements are the combination of 2 linear movements (primary & secondary) of the same frequency and a 90 degree phase gap.
// The desired angle, long and short amplitudes and frequency must be specified to compute the movement.
class EllipticMove
{
private:
    float angle;  // orientation angle (degrees))
    float lenA;   // length of longest diameter (degrees)
    float lenB;   // length of shortest diameter (degrees)
    float freq;     // frequency of the movement
    // primary movement
    float vx1;   // x speed of primary movement (deg/s)
    float vy1;   // y speed of primary movement (deg/s)
    float ax1;   // x accel of primary movement (deg/s²)
    float ay1;   // y accel of primary movement (deg/s²)
    // secondary movement
    bool bDual; // indicates dual movement combination (false when lenB is 0)
    float vx2;   // x speed of secondary movement (deg/s)
    float vy2;   // y speed of secondary movement (deg/s)
    float ax2;   // x accel of secondary movement (deg/s²)
    float ay2;   // y accel of secondary movement (deg/s²)
    
public:  
    EllipticMove();
    //~EllipticMove();

    // parameters
    void setAngle(float value) {angle = value;};
    void setLengthA(float value) {lenA = value;};
    void setLengthB(float value) {lenB = value;};
    void setFrequency(float value)  {freq = value;}    
    float getAngle() {return angle;};
    float getLenA() {return lenA;};
    float getLenB() {return lenB;};
    float getFrequency() {return freq;};
    
    // compute linear movements 
    void compute();

    // linear movements
    float getSpeedx1() {return vx1;}; 
    float getSpeedy1() {return vy1;}; 
    float getSpeedx2() {return vx2;}; 
    float getSpeedy2() {return vy2;}; 
    bool isDualMove() {return bDual;};
    float getAccelx1() {return ax1;}; 
    float getAccely1() {return ay1;}; 
    float getAccelx2() {return ax2;}; 
    float getAccely2() {return ay2;}; 
    
    std::string toString();
    
private:
    void reset();    
};
}
#endif

#ifndef __AMY_MOVE_MOVEMENT_H
#define __AMY_MOVE_MOVEMENT_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
// Class that represents an arm movement. 
// A movement is configured by setting its angle, intensity and duration. 
// The movement is then computed, converting those values into proper axis speeds (pan, tilt and radial) that will produce the movement.    
class Movement
{
private:
    static const float KPI_DIV_180;
    // paramater
    float basicSpeed;   // basic speed used for linear speed computation
    // logic
    float angle;        // movement direction in frontal plane (degrees)
    int millis;           // movement duration (milliseconds)
    float intensity;   // movement intensity
    float panSpeed;  // pan speed (deg/s)
    float tiltSpeed;  // tilt speed (deg/s)

public:    
    Movement();
//    ~Movement();
    
    void set(float angle, int time, float intensity = 1.0);
    
    void updateAngle(float value);
    void updateTime(int value);
    void updateIntensity(float value);    
    
    float getAngle() {return angle;}
    int getTime() {return millis;}
    float getIntensity() {return intensity;}    
    float getPanSpeed() {return panSpeed;}
    float getTiltSpeed() {return tiltSpeed;}
    
    std::string getDescription();
    
private:
    // computes axis speeds to achieve the movement
    void compute();
   
};
}
#endif

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "amy/move/data/Movement.h"

namespace amy
{
const float Movement::KPI_DIV_180 = 0.0174;    

Movement::Movement ()
{
    basicSpeed = 10.0;
    angle = 0.0;   
    millis = 0;     
    intensity = 0.0; 
    panSpeed = 0.0;
    tiltSpeed = 0.0;
}

void Movement::set(float angle, int millis, float intensity)
{
    this->angle = angle;   
    this->millis = millis;     
    this->intensity = fabs(intensity);    // use positive intensities     
    
    compute();
}
    
 void Movement::updateAngle(float value)
 {
     angle = value;     
     compute();
 }

 void Movement::updateTime(int value)
 {
     millis = value;     
 }
 
 void Movement::updateIntensity(float value)
 {
     intensity = value;     
     compute();
 }

 // Computes axis speeds to achieve the movement
 // vPan = vLinear * sin(angle)
 // vTilt / vPan = tg(angle)
void Movement::compute()
 {     
    float linearSpeed = intensity * basicSpeed;
    // compute axis speeds for given angle and intensity
    if (angle != 90 && angle != 270)
    {
        float radians = angle * KPI_DIV_180;
        panSpeed = linearSpeed * sin(radians);
        tiltSpeed = panSpeed * tan(radians);        
    }
    // singularities (tan(90) and tan(270) are infinite)
    else
    {
        panSpeed = 0.0;
        tiltSpeed = (angle == 90 ? linearSpeed : -linearSpeed);        
    }          
 }
 
std::string Movement::getDescription()
{
    return "Movement:[angle=" + std::to_string(angle) +
            ", millis=" + std::to_string(millis) +
            ", intensity=" + std::to_string(intensity) +
            ", panSpeed=" + std::to_string(panSpeed) +
            ", tiltSpeed=" + std::to_string(tiltSpeed) + "]"; 
}

}

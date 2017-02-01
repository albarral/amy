/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/move/SpeedSensor3.h"

namespace amy
{
SpeedSensor3::SpeedSensor3()
{
    speed1 = 0.0;          
    speed2 = 0.0;          
    speed3 = 0.0;      
    preValue1 = 0.0;          
    preValue2 = 0.0;          
    preValue3 = 0.0;          
}


void SpeedSensor3::sense(float value1, float value2, float value3)
{
    oClick.read();
    oClick.start();
    
    if (oClick.getMillis() !=0.0)
    {
        // we compute the inverse to use products instead of divisions (faster)
        float inverse_seconds = 1000.0/oClick.getMillis();
        
        speed1 = (value1 - preValue1)*inverse_seconds;
        speed2 = (value2 - preValue2)*inverse_seconds;
        speed3 = (value3 - preValue3)*inverse_seconds;        
    }
    preValue1 = value1;
    preValue2 = value2;
    preValue3 = value3;
}
}
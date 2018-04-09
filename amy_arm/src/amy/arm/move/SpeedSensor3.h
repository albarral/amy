#ifndef __AMY_MOVE_SPEEDSENSOR3_H
#define __AMY_MOVE_SPEEDSENSOR3_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron/util/Click.h"

namespace amy
{
// Class used to compute 3 variable speeds
class SpeedSensor3
{
private:
    float speed1;    // magnitude/s
    float speed2;    // magnitude/s      
    float speed3;    // magnitude/s  
    float preValue1;          
    float preValue2;          
    float preValue3;          
    tron::Click oClick;        // utility class for time computation

public:
        SpeedSensor3();
        //~SpeedSensor3();
                
        void sense(float val1, float val2, float val3);

        float getSpeed1() {return speed1;}
        float getSpeed2() {return speed2;}
        float getSpeed3() {return speed3;}
};
}
#endif

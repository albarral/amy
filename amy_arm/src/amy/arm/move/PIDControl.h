#ifndef __AMY_MOVE_PIDCONTROL_H
#define __AMY_MOVE_PIDCONTROL_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace amy
{
class PIDControl
{
private:
    // params
    float Kp;                   // P sensitivity
    float Ki;                   // I sensitivity
    float Kd;                   // D sensitivity
    // logic
    float output; 

public:
        PIDControl();
                
       void init(float kp, float ki, float kd);

       // perfprm PID control, output returnes
        float control(float error);
        float getOutput() {return output;}
        
};
}
#endif

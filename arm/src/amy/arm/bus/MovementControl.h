#ifndef __AMY_ARM_MOVEMENTCONTROL_H
#define __AMY_ARM_MOVEMENTCONTROL_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>

namespace amy
{
// Set of parameters that affect how movements are done.
// Shared by many modules. Thread safe.
class MovementControl
{
    private:     
        std::mutex mutex;
        int electricity;        // electricity of movements (affects acceleration)
        float time4move;    // time allowed for all movements
        const int minElectricity = 1;
        const int maxElectricity = 10;
        const float minTime4move = 0.5;
        const float maxTime4move = 5.0;
        int accel;  
        
    public:
        MovementControl();
                
        void setElectricity(int value);        
        void setTime4Move(float value);        

        int getElectricity();
        float getTime4Move();

        int getAccel();
        
private:
    void computeAcceleration();
};

}    
#endif

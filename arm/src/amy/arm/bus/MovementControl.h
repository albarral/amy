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
        const int minElectricity = 1;
        const int maxElectricity = 10;
        int accel; 
        
    public:
        MovementControl();
                
        void setElectricity(int value);        

        int getElectricity();

        int getAccel();
        
        
private:
    void computeAcceleration();
};

}    
#endif

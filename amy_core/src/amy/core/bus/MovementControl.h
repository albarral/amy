#ifndef __AMY_CORE_MOVEMENTCONTROL_H
#define __AMY_CORE_MOVEMENTCONTROL_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include <string>

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
        //int accel; 
        // axis driver params
        float Kaccel;                // acceleration sensitivity
        float Kspeed;              // speed sensitivity
        float driverTolerance;      // position tolerance for driver movements
        float driverSpeed;      // speed used for driver movements
        
    public:
        MovementControl();
                
        void setElectricity(int value);        

        int getElectricity();

        //int getAccel();

        // AxisDriver params
        void setKaccelDriver(float value);
        float getKaccelDriver();
        void setKspeedDriver(float value);
        float getKspeedDriver();
        void setDriverTolerance(float value);
        float getDriverTolerance();
        void setDriverSpeed(float value);
        float getDriverSpeed();
        
        // returns class description
        std::string toString();
        
private:
    //void computeAcceleration();
};

}    
#endif

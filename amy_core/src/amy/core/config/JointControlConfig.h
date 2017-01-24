#ifndef __AMY_CORE_JOINTCONTROLSECTION_H
#define __AMY_CORE_JOINTCONTROLSECTION_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
// Set of parameters that affect how movements are done.
// Shared by many modules. 
class JointControlConfig
{
    private:     
        int brakeAccel;      // degrees/s2
        // JointControl params
        float Kaccel;                // acceleration sensitivity
        float Kspeed;              // speed sensitivity
        float driverTolerance;      // position tolerance for driver movements
        float driverSpeed;      // speed used for driver movements
        
    public:
        JointControlConfig();
                
        void setBrakeAccel(int value) {brakeAccel = value;};
        int getBrakeAccel() {return brakeAccel;}

        void setKaccelDriver(float value) {Kaccel = value;};
        float getKaccelDriver() {return Kaccel;};
        
        void setKspeedDriver(float value) {Kspeed = value;};
        float getKspeedDriver() {return Kspeed;};
        
        void setDriverTolerance(float value) {driverTolerance = value;};
        float getDriverTolerance() {return driverTolerance;};
        
        void setDriverSpeed(float value) {driverSpeed = value;};
        float getDriverSpeed() {return driverSpeed;};
        
        // returns class description
        std::string toString();
        
};

}    
#endif

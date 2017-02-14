#ifndef __AMY_ARM_CONFIG_H
#define __AMY_ARM_CONFIG_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
// Parameters for amy_arm project.
class ArmConfig
{
    private:     
        // JointDriver modules
        int brakeAccel;      // degrees/s2
        // AxisDriver modules
        float driverKaccel;                // acceleration sensitivity
        float driverKspeed;              // speed sensitivity
        float driverTolerance;      // position tolerance for driver movements
        float driverSpeed;      // speed used for driver movements
        // TiltKeeper module
        float tiltKeeperPID[3];         // PID params for TiltKeeper module
        
        
    public:
        ArmConfig();
                
        void setBrakeAccel(int value) {brakeAccel = value;};
        int getBrakeAccel() {return brakeAccel;}

        void setDriverKaccel(float value) {driverKaccel = value;};
        float getDriverKaccel() {return driverKaccel;};        
        void setDriverKspeed(float value) {driverKspeed = value;};
        float getDriverKspeed() {return driverKspeed;};        
        void setDriverTolerance(float value) {driverTolerance = value;};
        float getDriverTolerance() {return driverTolerance;};        
        void setDriverSpeed(float value) {driverSpeed = value;};
        float getDriverSpeed() {return driverSpeed;};
        
        float* getTiltKeeperPID() {return tiltKeeperPID;};
        
        // returns class description
        std::string toString();
        
};

}    
#endif

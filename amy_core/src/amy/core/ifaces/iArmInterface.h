#ifndef __AMY_CORE_IARMINTERFACE_H
#define __AMY_CORE_IARMINTERFACE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


namespace amy
{
// Interface class to be implemented by any arm control library.
class iArmInterface
{
public:
    // check if it's enabled
    virtual bool isEnabled() = 0;
        
    // change arm pan
    virtual void movePan(float angle) = 0;
    // change arm tilt
    virtual void moveTilt(float angle) = 0;
    // extend arm
    virtual void extend(float value) = 0;

    // set HS position
    virtual void moveHS(float angle) = 0;
    // set VS position
    virtual void moveVS(float angle) = 0;
    // set EL position
    virtual void moveEL(float angle) = 0;
    // set HW position
    virtual void moveHW(float angle) = 0;
    // set VW position
    virtual void moveVW(float angle) = 0;

    /*
    // set HS acceleration (degrees/s²)
    virtual void accelHS(float accel) = 0;
    // set VS acceleration (degrees/s²)
    virtual void accelVS(float accel) = 0;
    // set EL acceleration (degrees/s²)
    virtual void accelEL(float accel) = 0;
    // set HW acceleration (degrees/s²)
    virtual void accelHW(float accel) = 0;
    // set VW acceleration (degrees/s²)
    virtual void accelVW(float accel) = 0;
     */ 
};

}    
#endif

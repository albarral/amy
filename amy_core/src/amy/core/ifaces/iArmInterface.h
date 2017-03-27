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

    // CYCLIC MOVEMENTS
    // set pan frequency (Hz)
    virtual void panFrequency(float value) = 0;
    // set pan amplitude (degrees)
    virtual void panAmplitude(float value) = 0;
    // trigger pan cyclic movement
    virtual void panTrigger() = 0;
    // stop pan cyclic movement
    virtual void panStop() = 0;

    // set tilt frequency (Hz)
    virtual void tiltFrequency(float value) = 0;
    // set tilt amplitude (degrees)
    virtual void tiltAmplitude(float value) = 0;
    // trigger tilt cyclic movement
    virtual void tiltTrigger() = 0;
    // stop tilt cyclic movement
    virtual void tiltStop() = 0;

    // AXIS SPEEDS
    // change pan speed
    virtual void panSpeed(float value) = 0;
    // change tilt speed
    virtual void tiltSpeed(float value) = 0;
    // change radial speed
    virtual void radialSpeed(float value) = 0;
    // keep arm tilt
    virtual void keepTilt(int value) = 0;
    
    // AXIS POSITIONS
    // change arm pan
    virtual void movePan(float angle) = 0;
    // change arm tilt
    virtual void moveTilt(float angle) = 0;
    // extend arm
    virtual void extend(float value) = 0;

    // JOINT POSITIONS
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
    
    // JOINT OUTPUTS    
    // get HS control angle
    virtual float getHSControl() = 0;
    // get VS control angle
    virtual float getVSControl() = 0;
    // get EL control angle
    virtual float getELControl() = 0;
    // get HW control angle
    virtual float getHWControl() = 0;
    // get VW control angle
    virtual float getVWControl() = 0;
};

}    
#endif

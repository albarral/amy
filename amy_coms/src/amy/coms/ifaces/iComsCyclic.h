#ifndef __AMY_COMS_ICOMSCYCLIC_H
#define __AMY_COMS_ICOMSCYCLIC_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace amy
{
// Interface class defining communication methods for controlling arm cyclic movements
class iComsCyclic
{    
public:
    // frontal cyclic movements
    virtual void frontFrequency(float value) = 0;
    virtual void frontAmplitude(float value) = 0;
    virtual void frontAngle(float value) = 0;
    virtual void frontStart() = 0;
    virtual void frontStop() = 0;
    // tilt cyclic movements
//    virtual void tiltFrequency(float value) = 0;
//    virtual void tiltAmplitude(float value) = 0;
//    virtual void tiltTrigger() = 0;
//    virtual void tiltStop() = 0;
};
}
#endif

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
    // pan cyclic movements
    virtual void panFrequency(float value) = 0;
    virtual void panAmplitude(float value) = 0;
    virtual void panTrigger() = 0;
    virtual void panStop() = 0;
    // tilt cyclic movements
    virtual void tiltFrequency(float value) = 0;
    virtual void tiltAmplitude(float value) = 0;
    virtual void tiltTrigger() = 0;
    virtual void tiltStop() = 0;
};
}
#endif

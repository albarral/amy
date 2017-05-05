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
    // ARM MOVER
    // launch this movement type
    virtual void launchMove(int value) = 0;
    // stop movement
    virtual void stopMove() = 0;
    // turn the movement these angle (degrees)
    virtual void turnMove(int value) = 0;
    // make movement wider/narrower
    virtual void moveWider(bool value) = 0;
    // make movement taller/shorter
    virtual void moveTaller(bool value) = 0;
    // make movement faster/slower
    virtual void moveFaster(bool value) = 0;
    
    // FRONTAL CYCLER
    virtual void frontFrequency(float value) = 0;
    virtual void frontAmplitude(float value) = 0;
    virtual void frontAngle(float value) = 0;
    virtual void frontStart() = 0;
    virtual void frontStop() = 0;
};
}
#endif

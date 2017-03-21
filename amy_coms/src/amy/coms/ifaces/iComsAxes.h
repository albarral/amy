#ifndef __AMY_COMS_ICOMSAXES_H
#define __AMY_COMS_ICOMSAXES_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace amy
{
// Interface class defining communication methods for controlling arm axes.
class iComsAxes
{    
public:
    // axis speeds
    virtual void panSpeed(float value) = 0;
    virtual void tiltSpeed(float value) = 0;
    virtual void radialSpeed(float value) = 0;
        
    // axis positions   
    virtual void movePan(float value) = 0;
    virtual void moveTilt(float value) = 0;
    virtual void moveRadius(float value) = 0;
};
}
#endif

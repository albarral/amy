#ifndef __AMY_COMS_ICOMSJOINTS_H
#define __AMY_COMS_ICOMSJOINTS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace amy
{
// Interface class defining communication methods for controlling arm joints.
class iComsJoints
{    
public:
    // joint positions
    virtual void setPosHS(float value) = 0;
    virtual void setPosVS(float value) = 0;
    virtual void setPosELB(float value) = 0;
    virtual void setPosHW(float value) = 0;
    virtual void setPosVW(float value) = 0;
};
}
#endif

#ifndef __AMY_COMS_IAMYCOMS_H
#define __AMY_COMS_IAMYCOMS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace amy
{
// Interface class defining the methods to be implemented by amy client and server classes.
class iAmyComs
{    
public:
    // arm control
    virtual void movePan(float value) = 0;
    virtual void moveTilt(float value) = 0;
    virtual void moveRadius(float value) = 0;
    // joint control
    virtual void setPosHS(float value) = 0;
    virtual void setPosVS(float value) = 0;
    virtual void setPosELB(float value) = 0;
    virtual void setPosHW(float value) = 0;
    virtual void setPosVW(float value) = 0;
    // process control
    virtual void endAmy() = 0;
};
}
#endif

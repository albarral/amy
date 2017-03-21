#ifndef __AMY_COMS_ICOMSOTHERS_H
#define __AMY_COMS_ICOMSOTHERS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace amy
{
// Interface class defining communication methods for controlling other arm actions.
class iComsOthers
{    
public:
    // keep arm tilt
    virtual void keepTilt(int value) = 0;    
    // end amy process
    virtual void endAmy() = 0;
};
}
#endif

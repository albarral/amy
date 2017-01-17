#ifndef __AMY_COMS_IAMYPUBLISHER_H
#define __AMY_COMS_IAMYPUBLISHER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


namespace amy
{
// Interface for amy publisher classes (used for publish-subscribe communications)
class iAmyPublisher
{    
public:
    // publish commanded joint control positions (angles)
    virtual void publishArmControl() = 0;
};
}
#endif

#ifndef __AMY_JOINT_CONTROL2_H
#define __AMY_JOINT_CONTROL2_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/move/JointMover.h"
#include "amy/arm/util/JointModule.h"

namespace amy
{
// Lower control module for a joint. Transforms the desired joint acceleration into proper joint positions.
// Speed and position can also be commanded.    
class JointControl2 : public JointModule
{
public:    
    static const int STATE_ON = 0;  // single state, always do the same
    
private:
    static log4cxx::LoggerPtr logger;
    // logic
    JointMover oJointMover;     // class where the real movement is generated

public:
        JointControl2();
        //~JointControl2();
                
       // module params
       virtual void init(Arm& oArm);
        
private:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        
        // read bus data
        void senseBus();
        // write data to bus (speed)
        void writeBus();
};
}
#endif

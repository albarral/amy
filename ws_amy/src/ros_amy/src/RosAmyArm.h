#ifndef __ROS_AMY_ARM_H
#define __ROS_AMY_ARM_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "comy/file/ComyFileSubscriber.h"
#include "talky/talk/Interpreter.h"
#include "talky2/arm/ArmJointAngles.h"

class RosAmyArm
{
private:    
    int counter;          
    comy::ComyFileSubscriber oComySubscriber;     // comy coms subscriber
    talky::Interpreter oInterpreter;                           // talky language interpreter        
    talky2::ArmJointAngles oJointAngles;                    // talky2 utility to process arm joints info
    talky2::ArmJointAngles oJointAngles0;                  // talky2 utility to process arm joints info
  
public:
  RosAmyArm();
  ~RosAmyArm();
    
  // runs the main while
  void runYoubot();
  void runUR5();
  
private:
    //void waitMoveDone(YoubotArm& oYoubotArm);
    
    bool processMessage(std::string rawMessage);    
    void showAngles();  
};

#endif

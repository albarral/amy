#ifndef __ROS_AMY_ARM_H
#define __ROS_AMY_ARM_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "comy/file/ComyFileSubscriber.h"
#include "talky/talk/Interpreter.h"
#include "amy/talk/DataBlockJoints.h"

class RosAmyArm
{
private:    
    int counter;          
    comy::ComyFileSubscriber oComySubscriberJoints;     // coms subscriber for arm topic & joint category
    talky::Interpreter oInterpreter;                                   // talky language interpreter        
    amy::DataBlockJoints oDataBlockJoints;                    // amy utility to process arm joints info
    amy::DataBlockJoints oDataBlockJoints0;                  // amy utility to process arm joints info
  
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

#ifndef __ROS_AMY_ARM_H
#define __ROS_AMY_ARM_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/data/ArmData.h"

class RosAmyArm
{
private:    
  int counter;  
  
public:
  RosAmyArm();
  ~RosAmyArm();
    
  // runs the main while
  void runYoubot();
  void runUR5();
  
private:
    //void waitMoveDone(YoubotArm& oYoubotArm);
    
    void showAngles(amy::ArmData& oArmData);
  
};

#endif

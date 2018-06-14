#ifndef __ROS_AMY_ARM_H
#define __ROS_AMY_ARM_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface/ArmListener.h"
#include "amy/interface/ArmSensors.h"

class RosAmyArm
{
private:    
    int counter;          
    amy::ArmListener oArmListener;         // listener utility for arm published info
    amy::JointsData jointPositions;           // structure for storing arm joints data
  
public:
  RosAmyArm();
  ~RosAmyArm();
    
  // runs the main while
  void runYoubot();
  void runUR5();
  
private:
    //void waitMoveDone(YoubotArm& oYoubotArm);
    
    bool compareData(amy::JointsData& jointPositions1, amy::JointsData& jointPositions2);    
    void showAngles(amy::JointsData& jointPositions);  
};

#endif

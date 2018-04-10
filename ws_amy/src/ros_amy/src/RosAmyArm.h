#ifndef __ROS_AMY_ARM_H
#define __ROS_AMY_ARM_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/talky/arm/ArmListener.h"
#include "tron2/robot/sensors/ArmSensors.h"

class RosAmyArm
{
private:    
    int counter;          
    tron2::ArmListener oArmListener;         // listener utility for arm published info
    tron2::JointsData jointPositions;           // structure for storing joints data
  
public:
  RosAmyArm();
  ~RosAmyArm();
    
  // runs the main while
  void runYoubot();
  void runUR5();
  
private:
    //void waitMoveDone(YoubotArm& oYoubotArm);
    
    bool compareData(tron2::JointsData& jointPositions1, tron2::JointsData& jointPositions2);    
    void showAngles(tron2::JointsData& jointPositions);  
};

#endif

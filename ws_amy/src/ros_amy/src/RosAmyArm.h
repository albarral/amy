#ifndef __ROS_AMY_ARM_H
#define __ROS_AMY_ARM_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron/talky2/arm/ArmListener.h"
#include "tron/robot/sensors/ArmSensors.h"

class RosAmyArm
{
private:    
    int counter;          
    tron::ArmListener oArmListener;         // listener utility for arm published info
    tron::JointsData jointPositions;           // structure for storing joints data
  
public:
  RosAmyArm();
  ~RosAmyArm();
    
  // runs the main while
  void runYoubot();
  void runUR5();
  
private:
    //void waitMoveDone(YoubotArm& oYoubotArm);
    
    bool compareData(tron::JointsData& jointPositions1, tron::JointsData& jointPositions2);    
    void showAngles(tron::JointsData& jointPositions);  
};

#endif

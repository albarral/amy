#ifndef __ROS_AMY_ARM_H
#define __ROS_AMY_ARM_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/sense/JointsListener.h"

struct JointsData
{
    float hs; 
    float vs; 
    float elb; 
    float hwri; 
    float vwri;   
};

class RosAmyArm
{
private:    
    int counter;          
    amy::JointsListener oJointsListener;         // amy listener for published arm joints
    JointsData joints;           // present arm joints data
    JointsData joints0;         // previous arm joints data
  
public:
  RosAmyArm();
  ~RosAmyArm();
    
  // runs the main while
  void runYoubot();
  void runUR5();
  
private:
    //void waitMoveDone(YoubotArm& oYoubotArm);
    
    bool senseJoints();
    bool checkChanged();    
    void showAngles(JointsData& jointPositions);  
};

#endif

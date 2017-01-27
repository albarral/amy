#ifndef __ROS_YOUBOT_ARM_H
#define __ROS_YOUBOT_ARM_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   ainoa@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <string>

#include <actionlib/client/simple_action_client.h>
#include "control_msgs/FollowJointTrajectoryAction.h"
#include "trajectory_msgs/JointTrajectoryPoint.h"

// Class for controlling a youbot arm by sending trajectories through ROS actions
class YoubotArm
{
private:        
    actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction>* oActionClient;    // Action client for the joint trajectory action (used to trigger the arm movement action)        
    control_msgs::FollowJointTrajectoryGoal goal;     // the message sent to the arm
    std::vector<std::string> listJointNames;
    int numJoints;
    float radsShoulderH;   // pan shoulder (in radians)
    float radsShoulderV;   // tilt shoulder (in radians)
    float radsElbow;         // elbow (in radians)
    float radsJoint4;         // 4th joint wrist tilt (in radians)
    float radsJoint5;         // 5th joint wrist rot(in radians)  
    // aux
    const float PI_DIV180 = 0.01745;

public:  
    YoubotArm() ;
    ~YoubotArm();

      // sets arm joint positions (shoulder & elbow) in degrees
      void setArmPos (float shoulderHAngle, float shoulderVAngle, float elbowAngle);
      // sets hand joint positions (wrist tilt & rot) in degrees
      void setHandPos (float joint4Angle, float joint5Angle);
      
      // Prepares the movement trajectory with the given delay (in seconds)
      void prepareMove(float delaySecs);

      //! Sends the command to start a given trajectory
      void move();   
      
      //! Returns the current state of the action
      bool isMoveDone()  {return oActionClient->getState().isDone();} 

      // TEMP for test
      void setTestTrajectory();
 
private:
     // builds a trajectory point with the last requested position (arm & hand)
     void setTrajectoryPoint (trajectory_msgs::JointTrajectoryPoint& point);
      // set arm & hand joint positions directly in radians
      void setArmPos2 (float shoulderHAngle, float shoulderVAngle, float elbowAngle);
      void setHandPos2 (float joint4Angle, float joint5Angle);
};
#endif
/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <ros/ros.h>

#include "UR5Arm.h"

UR5Arm::UR5Arm() 
{
    listJointNames.push_back("shoulder_pan_joint");
    listJointNames.push_back("shoulder_lift_joint");
    listJointNames.push_back("elbow_joint");
    listJointNames.push_back("wrist_1_joint");
    listJointNames.push_back("wrist_2_joint");
    listJointNames.push_back("wrist_3_joint");

    numJoints = listJointNames.size();
    
    // First, the joint names, which apply to all waypoints
    for (int i=0; i<numJoints; i++)
    {
        std::string jointName = listJointNames.at(i);
        goal.trajectory.joint_names.push_back(jointName);
    }
    
    // tell the action client that we want to spin a thread by default
    oActionClient = new actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction>("arm_controller/follow_joint_trajectory", true);

    // wait for action server to come up
//    while(!oActionClient->waitForServer(ros::Duration(1.0)))
//    {
//      ROS_INFO("Waiting for the joint_trajectory_action server");
//    }
    
    setArmPos2(0.0, 0.0, 0.0);
    setHandPos2(0.0, 0.0, 0.0);
}

//! Clean up the action client
UR5Arm::~UR5Arm()
{
    delete oActionClient;
}

// traslates degrees to radians for arm joints
void UR5Arm::setArmPos(float shoulderHAngle, float shoulderVAngle, float elbowAngle)
{
    radsShoulderH = shoulderHAngle * PI_DIV180;
    radsShoulderV = shoulderVAngle * PI_DIV180;
    radsElbow = elbowAngle * PI_DIV180;    
}

// traslates degrees to radians for hand joints
void UR5Arm::setHandPos(float wrist1Angle, float wrist2Angle, float wrist3Angle)
{
    radsWrist1 = wrist1Angle * PI_DIV180;
    radsWrist2 = wrist2Angle * PI_DIV180;
    radsWrist3 = wrist3Angle * PI_DIV180;
}

void UR5Arm::prepareMove(float delaySecs)
{
    // We will have two waypoints in this goal trajectory
    goal.trajectory.points.clear();
    goal.trajectory.points.resize(1);
    
    setTrajectoryPoint(goal.trajectory.points[0]);
    // To be reached delaySecs seconds after starting along the trajectory
    goal.trajectory.points[0].time_from_start = ros::Duration(delaySecs);
}

//! Sends the command to start a given trajectory
void UR5Arm::move()
{
    // When to start the trajectory: 1s from now
    goal.trajectory.header.stamp = ros::Time::now();
    oActionClient->sendGoal(goal);
}

void UR5Arm::setTrajectoryPoint (trajectory_msgs::JointTrajectoryPoint& point)
{
    // positions
    point.positions.resize(numJoints);
    point.positions[0] = radsShoulderH;
    point.positions[1] = radsShoulderV;
    point.positions[2] = radsElbow;
    point.positions[3] = radsWrist1;
    point.positions[4] = radsWrist2;
    point.positions[5] = radsWrist3;
    // velocities (all to 0))
    point.velocities.resize(numJoints);
    for (size_t j=0; j<numJoints; ++j)
    {
      point.velocities[j] = 0.0;
    }    
}

// directly in radians
void UR5Arm::setArmPos2(float shoulderHAngle, float shoulderVAngle, float elbowAngle)
{
    radsShoulderH = shoulderHAngle;
    radsShoulderV = shoulderVAngle;
    radsElbow = elbowAngle;    
}

// directly in radians
void UR5Arm::setHandPos2(float wrist1Angle, float wrist2Angle, float wrist3Angle)
{
    radsWrist1 = wrist1Angle;
    radsWrist2 = wrist2Angle;
    radsWrist3 = wrist3Angle;
}

void UR5Arm::setTestTrajectory()
{
    // We will have two waypoints in this goal trajectory
    goal.trajectory.points.clear();
    goal.trajectory.points.resize(1);
    
    // First trajectory point
    setArmPos(-20, 0.0, -30.0);
    setHandPos(0.0, 0.0, 0.0);
    setTrajectoryPoint(goal.trajectory.points[0]);
    // To be reached 1 second after starting along the trajectory
    goal.trajectory.points[0].time_from_start = ros::Duration(1.0);
}


/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

//#include <vector>
#include <log4cxx/xml/domconfigurator.h>

#include <ros/ros.h>
#include "RosAmyArm.h"
#include "YoubotArm.h"
#include "UR5Arm.h"

int main(int argc, char** argv) 
{
     // Init the ROS node
    ros::init(argc, argv, "RosAmyArm");
    
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");

    ros::Time::init(); 

    RosAmyArm oRosAmyArm;
    oRosAmyArm.runUR5();

    return (0);
}

RosAmyArm::RosAmyArm() 
{
}

RosAmyArm::~RosAmyArm()
{    
}
     
  void RosAmyArm::runUR5()
{
    ROS_INFO("RosAmyArm: keyLoop started");
        
    // set loop frequency
    float freq = 5.0;    
    ros::Rate rate(freq);
    float moveDelay = 0.20; // 200 ms
    bool bnewInfo;
    
    UR5Arm oUR5Arm;
    oUR5Arm.setHandPos(0.0, 0.0, 0.0); 
       
    // check listener connection
    if (!oArmListener.senseChannels())
    {
        ROS_ERROR("RosAmyArm: failed arm listener connections");
        return;
    }
        
    while (ros::ok()) 
    {
        // process callbacks
        ros::spinOnce();

        if (oArmListener.senseChannels())
        {            
            bnewInfo = !compareData(jointPositions, oArmListener.getJointPositions());            
        }            
        else
            bnewInfo = false;       
        
        // if new info received and different from previous one
        if (bnewInfo)
        {               
            // store data
            jointPositions = oArmListener.getJointPositions(); 

            showAngles(jointPositions);
    
            // set hshoulder, vshouler & elbow joints
            oUR5Arm.setArmPos(-jointPositions.hs, -jointPositions.vs, -jointPositions.elb);
            // set wrist & hand joints
            oUR5Arm.setHandPos(jointPositions.vwri, 0.0, 0.0);
            oUR5Arm.prepareMove(moveDelay);
            oUR5Arm.move();
        }
        rate.sleep();
    }    
    
    ROS_INFO("RosAmyArm: keyLoop end");

    return;
}

// check if given joint positions are the same
bool RosAmyArm::compareData(tron2::JointsData& jointPositions1, tron2::JointsData& jointPositions2)
{
    if (jointPositions1.hs == jointPositions2.hs &&
            jointPositions1.vs == jointPositions2.vs &&
            jointPositions1.elb == jointPositions2.elb &&
            jointPositions1.hwri == jointPositions2.hwri &&
            jointPositions1.vwri == jointPositions2.vwri)
        return true;
    else 
        return false;
}

void RosAmyArm::showAngles(tron2::JointsData& jointPositions)
{
    ROS_INFO("arm angles: %d, %d, %d", (int)jointPositions.hs, (int)jointPositions.vs, (int)jointPositions.elb);      
}

  
/*
  void RosAmyArm::runYoubot()
{
    ROS_INFO("RosAmyArm: keyLoop started");
        
    // set loop frequency
    float freq = 1.0;
    ros::Rate rate(freq);

    YoubotArm oYoubotArm;
    oYoubotArm.setHandPos(0.0, 0.0);
    
    sam::ArmManager oArmManager;
    oArmManager.init("youbot");
    if (!oArmManager.isEnabled())
        return;

    oArmManager.startModules();
    
    while (ros::ok()) 
    {
        // runYoubot callbacks
        ros::spinOnce();

        oArmManager.readSollAngles();
        std::vector<float>& listSollAngles = oArmManager.getSollAngles();
        
        if (listSollAngles != listPrevAngles)
        {
            showAngles(listSollAngles);
            
            oYoubotArm.setArmPos(listSollAngles.at(0), listSollAngles.at(1), listSollAngles.at(2));
            oYoubotArm.setHandPos(listSollAngles.at(3), 0.0);
            oYoubotArm.prepareMove(0.2);
            oYoubotArm.move();

            listPrevAngles = listSollAngles;            
        }
        rate.sleep();
    }    
    
    oArmManager.stopModules();
    
    ROS_INFO("RosAmyArm: keyLoop end");

    return;
}
 */

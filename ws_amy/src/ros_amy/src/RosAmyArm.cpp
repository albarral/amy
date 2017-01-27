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
#include "amy/coms/file/AmyZeroMQSubscriber.h"



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
      //oArmManager.stopModules();
  }
 

    
  void RosAmyArm::runUR5()
{
    ROS_INFO("RosAmyArm: keyLoop started");
        
    // set loop frequency
    float freq = 5.0;
    ros::Rate rate(freq);

    UR5Arm oUR5Arm;
    oUR5Arm.setHandPos(0.0, 0.0, 0.0);
    
    // create subscriber
    amy::AmyZeroMQSubscriber oAmyZeroMQSubscriber;
    oAmyZeroMQSubscriber.init();

    bool bok = oAmyZeroMQSubscriber.isEnabled();
       
    if (!bok)
    {
        ROS_ERROR("RosAmyArm: failed init of arm network");
        return;
    }
    // objects needed to operate with arm coms
    amy::ArmData oArmData;
    amy::ArmData oArmData0; // for storage of previous data
    oArmData0.reset();
    
    while (ros::ok()) 
    {
        // process callbacks
        ros::spinOnce();

        oArmData = oAmyZeroMQSubscriber.readArmControl();
        //oArmNetwork.getArmSoll(0, oArmData);
        showAngles(oArmData);
        
        if (!oArmData.sameSollValues(oArmData0))
        {            
            // set hshoulder, vshouler & elbow joints
            oUR5Arm.setArmPos(-oArmData.getSollHS(), -oArmData.getSollVS(), -oArmData.getSollEL());
            // set wrist & hand joints
            oUR5Arm.setHandPos(oArmData.getSollVW(), 0.0, 0.0);
            oUR5Arm.prepareMove(0.2);
            oUR5Arm.move();

            // store data for next iteration
            oArmData0 = oArmData;
        }
        rate.sleep();
    }    
    
    ROS_INFO("RosAmyArm: keyLoop end");

    return;
}

  
void RosAmyArm::showAngles(amy::ArmData& oArmData)
{
    ROS_INFO("soll angles: %d, %d, %d, %d", (int)oArmData.getSollHS(), (int)oArmData.getSollVS(), (int)oArmData.getSollEL(), (int)oArmData.getSollVW());      
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

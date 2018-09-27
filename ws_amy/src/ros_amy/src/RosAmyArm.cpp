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
       
    while (ros::ok()) 
    {
        // process callbacks
        ros::spinOnce();

        // if new joints info received 
        if (senseJoints())
        {            
            // and joints info changed, update arm position
            if (checkChanged())
            {               
                // store data for next check
                joints0 = joints;

                showAngles(joints);

                // set hshoulder, vshouler & elbow joints
                oUR5Arm.setArmPos(-joints.hs, -joints.vs, -joints.elb);
                // set wrist & hand joints
                oUR5Arm.setHandPos(joints.vwri, 0.0, 0.0);
                oUR5Arm.prepareMove(moveDelay);
                oUR5Arm.move();
            }
        }            
        else
            bnewInfo = false;       
        
        rate.sleep();
    }    
    
    ROS_INFO("RosAmyArm: keyLoop end");

    return;
}

bool RosAmyArm::senseJoints()
{    
    bool bnew1 = oJointsListener.senseHS(joints.hs);
    bool bnew2 = oJointsListener.senseVS(joints.vs);
    bool bnew3 = oJointsListener.senseELB(joints.elb);
    bool bnew4 = oJointsListener.senseHWRI(joints.hwri);
    bool bnew5 = oJointsListener.senseVWRI(joints.vwri);
    
    return (bnew1 || 
            bnew2 ||
            bnew3 ||
            bnew4 ||
            bnew5 );
}
  
// check if joint positions have changed
bool RosAmyArm::checkChanged()
{
    if (joints.hs != joints0.hs ||
        joints.vs != joints0.vs ||
        joints.elb != joints0.elb ||
        joints.hwri != joints0.hwri ||
        joints.vwri != joints0.vwri)
        return true;
    else
        return false;
}

void RosAmyArm::showAngles(JointsData& joints)
{
    ROS_INFO("arm angles: %d, %d, %d", (int)joints.hs, (int)joints.vs, (int)joints.elb);      
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

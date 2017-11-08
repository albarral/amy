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
#include "talky/Topics.h"
#include "talky/coms/CommandBlock.h"
#include "talky/languages/ArmLanguage.h"

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
    
    UR5Arm oUR5Arm;
    oUR5Arm.setHandPos(0.0, 0.0, 0.0); 
   
    // prepare interpreter for arm topic communications
    oInterpreter.addLanguage(talky::Topics::eTOPIC_ARM);    
    
    // prepare coms subscriber
    talky::ArmLanguage oArmLanguage;
    // prepare communication servers
    oComySubscriberJoints.connect(talky::Topics::ARM_TOPIC, oArmLanguage.CAT_ARM_JOINT);
    
    // prepare coms subscriber
    if (!oComySubscriberJoints.isConnected())
    {
        ROS_ERROR("RosAmyArm: failed connection of comy subscriber");
        return;
    }
    
    // reset joints info
    oDataBlockJoints0.resetData();    
    bool bnewInfo;
    
    while (ros::ok()) 
    {
        // process callbacks
        ros::spinOnce();

        if (oComySubscriberJoints.readMessage())
        {            
            bnewInfo = processMessage(oComySubscriberJoints.getRawMessage());            
        }            
        else
            bnewInfo = false;       
        
        // if new info received and different from previous one
        if (bnewInfo && !oDataBlockJoints.isEqual(oDataBlockJoints0))
        {                        
            showAngles();
    
            // set hshoulder, vshouler & elbow joints
            oUR5Arm.setArmPos(-oDataBlockJoints.getPosHS(), -oDataBlockJoints.getPosVS(), -oDataBlockJoints.getPosEL());
            // set wrist & hand joints
            oUR5Arm.setHandPos(oDataBlockJoints.getPosVW(), 0.0, 0.0);
            oUR5Arm.prepareMove(moveDelay);
            oUR5Arm.move();

            // store data for next iteration
            oDataBlockJoints0 = oDataBlockJoints;
        }
        rate.sleep();
    }    
    
    ROS_INFO("RosAmyArm: keyLoop end");

    return;
}


bool RosAmyArm::processMessage(std::string rawMessage)
{
    bool bret = false;

    // interpret received message
    if (oInterpreter.processMessage(rawMessage))
    {
        // if message block
        if (oInterpreter.isBlockProcessed())
        {
            // show obtained command block
            // ROS_INFO("RosAmyArm: %s", oInterpreter.getCommandBlock().toString());        

            // process interpreted command block
            bret = oDataBlockJoints.readBlock(oInterpreter.getCommandBlock());
        }
        // if simple message
        else
        {
            ROS_INFO("RosAmyArm: simple msg received, ignore");
        }            
    }
    else
    {
        ROS_WARN("RosAmyArm: message processing failed!");            
    }

    return bret;    
}

void RosAmyArm::showAngles()
{
    ROS_INFO("arm angles: %d, %d, %d", (int)oDataBlockJoints.getPosHS(), (int)oDataBlockJoints.getPosVS(), (int)oDataBlockJoints.getPosEL());      
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

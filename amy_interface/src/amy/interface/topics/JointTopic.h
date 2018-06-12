#ifndef __AMY_INTERFACE_ARM_JOINTTOPIC_H
#define __AMY_INTERFACE_ARM_JOINTTOPIC_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/robot/Topic.h"

namespace amy
{
// Concepts definition for the arm joint topic
 class JointTopic : public tron2::Topic
{
 public:
    /*! joint concepts */
    enum eConcepts
    {
         eJOINT_HS_POS,                         /*! horizontal shoulder position (degrees)*/
         eJOINT_VS_POS,                         /*! vertical shoulder position (degrees) */
         eJOINT_ELB_POS,                        /*! elbow position (degrees) */
         eJOINT_HWRI_POS,                      /*! horizontal wrist position (degrees) */
         eJOINT_VWRI_POS,                      /*! vertical wrist position (degrees) */
         eJOINT_DIM
    };

    /*! joint concepts names */
    const std::string JOINT_HS_POS = "hs";          /*! horizontal shoulder position */
    const std::string JOINT_VS_POS = "vs";          /*! vertical shoulder position  */
    const std::string JOINT_ELB_POS = "elb";        /*! elbow position  */
    const std::string JOINT_HWRI_POS = "hwri";     /*! horizontal wrist position */
    const std::string JOINT_VWRI_POS = "vwri";      /*! vertical wrist  position */

 public:    
    JointTopic(); 
    
 private: 
    virtual void fillConcepts();      
};
}
#endif

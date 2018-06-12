#ifndef __AMY_INTERFACE_ARM_AXISTOPIC_H
#define __AMY_INTERFACE_ARM_AXISTOPIC_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/robot/Topic.h"

namespace amy
{
// Concepts definition for the arm axis topic
 class AxisTopic : public tron2::Topic
{
 public:
    /*! axis concepts  */
    enum eConcepts
    {
         eAXIS_PAN_POS,                       /*! pan position (degrees) */
         eAXIS_TILT_POS,                       /*! tilt position (degrees) */
         eAXIS_RAD_POS,                       /*! radial position (cm) */
         eAXIS_PAN_SPEED,                     /*! pan speed (degrees/s) */
         eAXIS_TILT_SPEED,                     /*! tilt speed (degrees/s) */
         eAXIS_RAD_SPEED,                     /*! radial speed (cm/s) */
         eAXIS_KEEP_TILT,                       /*! keep the tilt position */         
         eAXIS_DIM
    };

    /*! axis concepts names */
    const std::string AXIS_PAN_POS = "pan";                 /*! pan position (degrees) */
    const std::string AXIS_TILT_POS = "tilt";                   /*! tilt position (degrees) */
    const std::string AXIS_RAD_POS = "rad";                  /*! radial position (cm) */
    const std::string AXIS_PAN_SPEED = "vpan";            /*! pan speed (degrees/s) */
    const std::string AXIS_TILT_SPEED = "vtilt";              /*! tilt speed (degrees/s) */
    const std::string AXIS_RAD_SPEED = "vrad";             /*! radial speed (cm/s) */
    const std::string AXIS_KEEP_TILT = "keeptilt";               /*! keep the tilt position */

 public:    
    AxisTopic(); 
    
 private: 
    virtual void fillConcepts();      
    
};
}
#endif

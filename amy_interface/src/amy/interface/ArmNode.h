#ifndef __AMY_INTERFACE_ARMNODE_H
#define __AMY_INTERFACE_ARMNODE_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/robot/Node.h"
#include "tron2/robot/Topic.h"

namespace amy
{
// Definition of arm node topics
 class ArmNode : public tron2::Node
{
public:
    /*! arm topics */
    enum eArmTopics
    {
        eARM_JOINT,                  /*! joint topic */
        eARM_AXIS,                   /*! axis topic  */
        eARM_CYCLIC,             /*! cyclic topic  */
        eARM_DIM
    };

    /*! arm node channels */
    enum eArmChannels
    {
        eARM_JOINTS_CHANNEL,             /*! joints channel */
        eARM_AXES_CHANNEL,                /*! axes channel  */
        eARM_CYCLER1_CHANNEL,          /*! cycler 1 channel  */
        eARM_CYCLER2_CHANNEL,          /*! cycler 2 channel  */
        eARM_EXTRA_CHANNEL,              /*! extra channel  */
        eARM_CHANNELS_DIM
    };     
    
    /*! arm topic names */
    static const std::string ARM_JOINT;
    static const std::string ARM_AXIS;
    static const std::string ARM_CYCLIC;

 public:     
     ArmNode();
     
     static tron2::Topic* getTopic4Channel(int channel);  
     
private:
     virtual void fillTopics();
};
}
#endif

#ifndef __AMY_INTERFACE_ARM_CYCLICTOPIC_H
#define __AMY_INTERFACE_ARM_CYCLICTOPIC_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/robot/Topic.h"

namespace amy
{
// Concepts definition for the arm cyclic topic
 class CyclicTopic : public tron2::Topic
{
 public:
    /*! cyclic concepts  */
    enum eConcepts
    {
         eCYCLIC_MAIN_FREQ,            /*! frequency of main cyclic component (Hz) */
         eCYCLIC_MAIN_AMP,             /*! amplitude of main cyclic component  (degrees) */
         eCYCLIC_MAIN_ANGLE,          /*! orientation of main cyclic component (degrees) */
         eCYCLIC_MAIN_PHASE,          /*! phase of main cyclic component (degrees) */
         eCYCLIC_SEC_FREQ,            /*! frequency of secondary cyclic component (Hz) */
         eCYCLIC_SEC_AMP,             /*! amplitude of secondary cyclic component (degrees) */
         eCYCLIC_SEC_ANGLE,          /*! orientation of secondary cyclic component (degrees) */
         eCYCLIC_SEC_PHASE,          /*! phase of secondary cyclic component (degrees) */
         eCYCLIC_ACTION,                  /*! start/stop cycler movement */
         eCYCLIC_DIM
    };

    /*! cyclic concept names */
    const std::string CYCLIC_MAIN_FREQ = "freq";      /*! frequency of main cyclic component (Hz) */
    const std::string CYCLIC_MAIN_AMP = "amp";        /*! amplitude of main cyclic component (degrees) */
    const std::string CYCLIC_MAIN_ANGLE = "angle";      /*! orientation of main cyclic component (degrees) */
    const std::string CYCLIC_MAIN_PHASE = "phase";  /*! phase of main cyclic component (degrees) */
    const std::string CYCLIC_SEC_FREQ = "freq2";      /*! frequency of secondary cyclic component (Hz) */
    const std::string CYCLIC_SEC_AMP = "amp2";        /*! amplitude of secondary cyclic component (degrees) */
    const std::string CYCLIC_SEC_ANGLE = "angle2";      /*! orientation of secondary cyclic component (degrees) */
    const std::string CYCLIC_SEC_PHASE = "phase2";  /*! phase of secondary cyclic component (degrees) */
    const std::string CYCLIC_ACTION = "go";                  /*! start/stop cyclic movement */

 public:    
    CyclicTopic(); 
    
 private: 
    virtual void fillConcepts();      
    
};
}
#endif

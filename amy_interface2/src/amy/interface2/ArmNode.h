#ifndef __AMY_INTERFACE2_ARMNODE_H
#define __AMY_INTERFACE2_ARMNODE_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron/topics/Node.h"

namespace amy
{
// Definition of arm node sections and channels
 class ArmNode2 : public tron::Node
{
public:
    /*! arm sections */
    enum eArmSections
    {
        eSECTION_JOINTS,             /*! joints section */
        eSECTION_AXES,                /*! axes section  */
        eSECTION_CYCLER1,          /*! cycler 1 section  */
        eSECTION_CYCLER2,          /*! cycler 2 section  */
        eSECTION_EXTRA,             /*! extra section  */
        eSECTION_DIM
    };     

    /*! joints section channels */
    enum eJointsChannels
    {
         eJOINTS_HS,                         /*! horizontal shoulder position (degrees)*/
         eJOINTS_VS,                         /*! vertical shoulder position (degrees) */
         eJOINTS_ELB,                        /*! elbow position (degrees) */
         eJOINTS_HWRI,                      /*! horizontal wrist position (degrees) */
         eJOINTS_VWRI,                      /*! vertical wrist position (degrees) */
         eJOINTS_DIM
    };

    /*! axes section channels  */
    enum eAxesChannels
    {
         eAXES_PAN,                       /*! pan position (degrees) */
         eAXES_TILT,                       /*! tilt position (degrees) */
         eAXES_RAD,                       /*! radial position (cm) */
         eAXES_PAN_SPEED,                     /*! pan speed (degrees/s) */
         eAXES_TILT_SPEED,                     /*! tilt speed (degrees/s) */
         eAXES_RAD_SPEED,                     /*! radial speed (cm/s) */
         eAXES_KEEP_TILT,                       /*! keep the tilt position */         
         eAXES_DIM
    };
    
    /*! cycler section channels  */
    enum eCyclerChannels
    {
         eCYCLER_MAIN_FREQ,            /*! frequency of main cyclic component (Hz) */
         eCYCLER_MAIN_AMP,             /*! amplitude of main cyclic component  (degrees) */
         eCYCLER_MAIN_ANGLE,          /*! orientation of main cyclic component (degrees) */
         eCYCLER_MAIN_PHASE,          /*! phase of main cyclic component (degrees) */
         eCYCLER_SEC_FREQ,            /*! frequency of secondary cyclic component (Hz) */
         eCYCLER_SEC_AMP,             /*! amplitude of secondary cyclic component (degrees) */
         eCYCLER_SEC_ANGLE,          /*! orientation of secondary cyclic component (degrees) */
         eCYCLER_SEC_PHASE,          /*! phase of secondary cyclic component (degrees) */
         eCYCLER_ACTION,                  /*! start/stop cycler movement */
         eCYCLER_DIM
    };
    
 private:
    /*! names of arm sections */
    const std::string SECTION_JOINTS = "joints";
    const std::string SECTION_AXES = "axes";
    const std::string SECTION_CYCLER1 = "cycler1";
    const std::string SECTION_CYCLER2 = "cycler2";
    
    /*! names of joints section channel */
    const std::string JOINTS_HS = "hs";          /*! horizontal shoulder position */
    const std::string JOINTS_VS = "vs";          /*! vertical shoulder position  */
    const std::string JOINTS_ELB = "elb";        /*! elbow position  */
    const std::string JOINTS_HWRI = "hwri";     /*! horizontal wrist position */
    const std::string JOINTS_VWRI = "vwri";      /*! vertical wrist  position */
    
    /*! names of axes section channels */
    const std::string AXES_PAN = "pan";                 /*! pan position (degrees) */
    const std::string AXES_TILT = "tilt";                   /*! tilt position (degrees) */
    const std::string AXES_RAD = "rad";                  /*! radial position (cm) */
    const std::string AXES_PAN_SPEED = "vpan";            /*! pan speed (degrees/s) */
    const std::string AXES_TILT_SPEED = "vtilt";              /*! tilt speed (degrees/s) */
    const std::string AXES_RAD_SPEED = "vrad";             /*! radial speed (cm/s) */
    const std::string AXES_KEEP_TILT = "keeptilt";               /*! keep the tilt position */
    
    /*! names of cycler section channels */
    const std::string CYCLER_MAIN_FREQ = "freq";      /*! frequency of main cyclic component (Hz) */
    const std::string CYCLER_MAIN_AMP = "amp";        /*! amplitude of main cyclic component (degrees) */
    const std::string CYCLER_MAIN_ANGLE = "angle";      /*! orientation of main cyclic component (degrees) */
    const std::string CYCLER_MAIN_PHASE = "phase";  /*! phase of main cyclic component (degrees) */
    const std::string CYCLER_SEC_FREQ = "freq2";      /*! frequency of secondary cyclic component (Hz) */
    const std::string CYCLER_SEC_AMP = "amp2";        /*! amplitude of secondary cyclic component (degrees) */
    const std::string CYCLER_SEC_ANGLE = "angle2";      /*! orientation of secondary cyclic component (degrees) */
    const std::string CYCLER_SEC_PHASE = "phase2";  /*! phase of secondary cyclic component (degrees) */
    const std::string CYCLER_ACTION = "go";                  /*! start/stop cyclic movement */
     
    void setJointsSection();
    void setAxesSection();
    void setCyclerSection(int section);
    
 public:     
   ArmNode2();
    
    // return node description
    virtual std::string toString() override;             
};
}
#endif

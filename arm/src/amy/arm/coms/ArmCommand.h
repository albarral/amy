#ifndef __AMY_ARM_COMMANDS_H
#define __AMY_ARM_COMMANDS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
/** 
 *  Utility class used to move the arm from external processes. 
 *  External commands are transformed into proper internal commands that will be sent to the corresponding arm control modules through the arm's bus.
 */
class ArmCommand
{
public:
    /*! action identifiers */
    enum eAction
    {
         eACT_UNDEFINED,                /*! undefined action */
         eACT_ARM_END,                   /*! end all arm control modules */
         eACT_ARM_STOP,                 /*! stop movements of all joints*/
         eACT_MOVEMENT_START,       /*! launch a predefined movement */
         eACT_MOVEMENT_STOP,        /*! stop any predefined movement */
         eACT_SET_PAN,                    /*! move arm's pan */
         eACT_SET_TILT,                    /*! move arm's tilt */
         eACT_SET_EXTENSION,          /*! extend arm */
         eACT_JOINT_BRAKE,              /*! brake (stop softly) a joint */
         eACT_JOINT_STOP,                /*! stop (abruptly) a joint */
         eACT_JOINT_ANGLE,                 /*! move a joint to a given position (angle) */
         eACT_DIM
    };

    /*! joint identifiers */
    enum eJoint
    {
         eJOINT_UNDEFINED,    /*! undefined joint */
         eJOINT_HSHOULDER,  /*! horizontal shoulder */
         eJOINT_VSHOULDER,  /*! vertical shoulder */
         eJOINT_ELBOW,         /*! elbow */
         eJOINT_VWRIST,        /*! vertical wrist */
         eJOINT_DIM
    };

    /*! module identifiers */
    enum eModule
    {
         eMOD_UNDEFINED,        /*! undefined module */
         eMOD_MANAGER,           /*! ArmManager */
         eMOD_ARMMOVER,         /*! ArmMover module */
         eMOD_ARMPANNER,   
         eMOD_ARMTILTER,     
         eMOD_ARMEXTENDER,  
         eMOD_JOINTMOVER,       /*! JointMover modules */
         eMOD_JOINTCONTROL,   /*! JointControl modules */
         eMOD_DIM
    };
    
private:
    int targetAction;   /*! action to be performed (one of eAction values)*/
    std::string targetJoint;   /*! joint affected by the action */
    int targetValue;   /*! value applied to the action */

    int busModule; /*! module to which the command must be sent (one of eModule values)*/    
    int busAction;   /*! action to be performed (internal code in the modules) */
    
public:
    ArmCommand();

    bool setTargetAction(int action);
    void setTargetJoint(std::string jointName) {targetJoint = jointName;};
    void setTargetValue(int value) {targetValue=value;};
    int getTargetAction() {return targetAction;};
    std::string getTargetJoint() {return targetJoint;};
    int getTargetValue() {return targetValue;};

    void setBusModule(int module) {busModule=module;};
    void setBusAction(int action) {busAction=action;};
    int getBusModule() {return busModule;};
    int getBusAction() {return busAction;};

    /*! resets arm command values */
    void resetCommand();    
    /*! builds a proper control command to be sent though the bus */
    bool buildBusCommand();    
    /*! checks if target action is for a specific target joint */    
    static bool isJointAction(int action);
};
}
#endif

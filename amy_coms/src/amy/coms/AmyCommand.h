#ifndef __AMY_COMS_AMYCOMMAND_H
#define __AMY_COMS_AMYCOMMAND_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
/** 
 * Class to represent amy commands. Used for communicating with amy from external processes.
 * It involves 3 elements: action, target and value.
 * Before transmission, the command must be converted to textual form (
 * On reception, it must be converted back to interpret it
 */
class AmyCommand
{
public:
    /*! action identifiers */
    enum eAction
    {
         eACT_UNDEFINED,                /*! undefined action */
         eACT_MOVE_ARM,                /*! move arm as a whole */
         eACT_MOVE_JOINT,              /*! move specific joint*/
         eACT_END_AMY,          /*! end amy process */
         eACT_DIM
    };

    /*! target identifiers */
    enum eTarget
    {
         eTAR_UNDEFINED,        /*! undefined target */
         eTAR_PAN,                  /*! arm's pan */
         eTAR_TILT,                  /*! arm's tilt */
         eTAR_RADIUS,             /*! arm's radius */
         eTAR_JOINT_HSHOULDER,          /*! horizontal shoulder */
         eTAR_JOINT_VSHOULDER,          /*! vertical shoulder */
         eTAR_JOINT_ELBOW,                 /*! elbow */
         eTAR_JOINT_VWRIST,                 /*! vertical wrist */
         eTAR_DIM
    };

    
private:
    int action;   /*! action to be performed (one of eAction values)*/
    int target;   /*! element affected by the action (one of eTarget value)*/
    float value;   /*! value applied by the action */
    std::string text;      /*! command textual form */    
    const std::string separator = "*";

    
public:
    AmyCommand();
    // clears the command
    void reset();

    int getAction() {return action;};
    int getTarget() {return target;};
    float getValue() {return value;};
    std::string getText() {return text;};
        
    /*! builds an amy textual command with the given elements */
    /*! returns true if valid, false otherwise */    
    bool buildCommand(int action, int target, float value=0.0);
    
    /*! interprets an amy command from its textual form */
    /*! returns true if valid, false otherwise */    
    bool interpret(std::string text);

    // checks if it's an arm command
    bool isArmCommand();
    // checks if it's a joint command
    bool isJointCommand();
    // checks if it's an amy command
    bool isAmyCommand();

private:
    // describe action 
    std::string describeAction(int value);
    // describe target
    std::string describeTarget(int value);
};
}
#endif

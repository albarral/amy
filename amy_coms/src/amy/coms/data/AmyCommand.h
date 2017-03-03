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
 * It involves 3 elements: category, action and value.
 * For its transmission, the command must be converted to textual form.
 * On reception, the textual form is analyzed and the command interpreted.
 */
class AmyCommand
{
public:
    /*! command categories */
    enum eCategories
    {
         eCAT_UNDEF,                    /*! undefined category */
         eCAT_JOINT_CMD,                /*! command of joint category */
         eCAT_AXIS_CMD,                 /*! command of axis category */
         eCAT_ARM_CMD,                /*! command of arm category */
         eCAT_AMY_CMD,                /*! command of amy category */
         eCAT_DIM
    };

    /*! actions of joint category */
    enum eJointActions
    {
         eJOINT_UNDEF,                             /*! undefined joint action */
         eJOINT_HS_POS,                         /*! horizontal shoulder position */
         eJOINT_VS_POS,                         /*! vertical shoulder position  */
         eJOINT_ELB_POS,                        /*! elbow position  */
         eJOINT_HWRI_POS,                      /*! horizontal wrist position */
         eJOINT_VWRI_POS,                      /*! vertical wrist  position */
         eJOINT_DIM
    };

    /*! actions of axis category  */
    enum eAxisActions
    {
         eAXIS_UNDEF,                          /*! undefined axis action */
         eAXIS_PAN_POS,                       /*! pan position */
         eAXIS_TILT_POS,                       /*! tilt position */
         eAXIS_RAD_POS,                       /*! radial position */
         eAXIS_PAN_SPEED,                     /*! pan speed */
         eAXIS_TILT_SPEED,                     /*! tilt speed */
         eAXIS_RAD_SPEED,                      /*! radial speed */
         eAXIS_DIM
    };

    /*! actions of arm category  */
    enum eArmActions
    {
         eARM_UNDEF,                          /*! undefined arm action */
         eARM_STOP,                           /*! stop arm */
         eARM_KEEP_TILT,                     /*! keep tilt position */
         eARM_DIM
    };

    /*! actions of amy category  */
    enum eAmyctions
    {
         eAMY_UNDEF,                          /*! undefined amy action */
         eAMY_END,                              /*! end amy program */
         eAMY_DIM
    };
        
private:
    int category;   /*! command category (eCategory) */
    int action;   /*! action to be performed (one of eAction values) */
    float value;   /*! value applied by the action */
    std::string text;      /*! command textual form */    
    const std::string separator = "*";
    
public:
    AmyCommand();
    // clears the command
    void reset();

    int getCategory() {return category;};
    int getAction() {return action;};
    float getValue() {return value;};
    std::string getText() {return text;};
        
    /*! builds an amy textual command with the given elements */
    /*! returns true if valid, false otherwise */    
    bool buildCommand(int category, int action, float value=0.0);
    
    /*! interprets an amy command from its textual form */
    /*! returns true if valid, false otherwise */    
    bool interpret(std::string text);
    
    // describe command
    std::string getDescription();    

private:    
    // check valid values
    bool isValidCategory(int value);
    bool isValidAction(int cat, int value);
    bool isValidJointAction(int value);
    bool isValidAxisAction(int value);
    bool isValidArmAction(int value);
    bool isValidAmyAction(int value);
    
    // describe category
    std::string describeCategory(int value);
    // describe action 
    std::string describeAction(int cat, int value);
    // describe action of joint category
    std::string describeJointAction(int value);
    // describe action of axis category
    std::string describeAxisAction(int value);
    // describe action of arm category
    std::string describeArmAction(int value);
    // describe action of amy category
    std::string describeAmyAction(int value);
};
}
#endif

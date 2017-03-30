#ifndef __AMY_COMS_JOINTCOMMAND_H
#define __AMY_COMS_JOINTCOMMAND_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/coms/data/AmyCommand.h"

namespace amy
{
// Class to represent joint commands. 
 class JointCommand : public AmyCommand
{
//public:
//    /*! actions of joint category */
//    enum eJointActions
//    {
//         eJOINT_UNDEF,                             /*! undefined joint action */
//         eJOINT_HS_POS,                         /*! horizontal shoulder position */
//         eJOINT_VS_POS,                         /*! vertical shoulder position  */
//         eJOINT_ELB_POS,                        /*! elbow position  */
//         eJOINT_HWRI_POS,                      /*! horizontal wrist position */
//         eJOINT_VWRI_POS,                      /*! vertical wrist  position */
//         eJOINT_DIM
//    };
        
    
public:
    JointCommand(int action, float value);

    // describe action 
    //virtual std::string describeAction();
};
}
#endif

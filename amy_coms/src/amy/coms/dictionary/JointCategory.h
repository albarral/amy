#ifndef __AMY_COMS_JOINTCATEGORY_H
#define __AMY_COMS_JOINTCATEGORY_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/dictionary/ComsCategory.h"

namespace amy
{
// Class used to hold all communication commands of the joints category .
 class JointCategory: public ComsCategory
{
public:
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

    JointCategory(); 

    // check if given action is valid for this category
    static bool isValidAction(int value);
    // describe given action name for this category
    static std::string describeAction(int value);

 private:    
    // builds category with a list of commands
    virtual void build();
};
}
#endif

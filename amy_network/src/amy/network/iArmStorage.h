#ifndef __AMY_IARM_STORAGE_H
#define __AMY_IARM_STORAGE_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/network/ArmData.h"

namespace amy
{
// Interface class for storage of arm's data
class iArmStorage
{
    public:
        // sets soll (commanded) values for all joints
        virtual bool storeArmSoll(int arm, ArmData& oArmData) = 0;
        // gets soll (commanded) values for all joints
        virtual bool readArmSoll(int arm, ArmData& oArmData) = 0;        
        // sets ist (measured) values for all joints
        virtual bool storeArmIst(int arm, ArmData& oArmData) = 0;
        // gets ist (measured) values for all joints
        virtual bool readArmIst(int arm, ArmData& oArmData) = 0;      
};

}    
#endif

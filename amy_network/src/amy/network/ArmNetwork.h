#ifndef __AMY_ARM_NETWORK_H
#define __AMY_ARM_NETWORK_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/network/ArmData.h"
#include "amy/network/iArmStorage.h"

namespace amy
{
// This class manages the amy's network for arms control
class ArmNetwork
{
public:
        // types of arm network
        enum eType
        {
            eNETWORK_DB,  /*! network data stored in DB */
            eNETWORK_DIM 
        };

    private:
        static log4cxx::LoggerPtr logger;
        bool benabled;
        iArmStorage* pArmStorage;

    public:
        ArmNetwork();
        ~ArmNetwork();

        // initializes the arms network (of the specified type)
        bool init(int type);
        
        // sets joint soll (commanded) values for the given arm
        bool setArmSoll(int arm, ArmDataN& oArmData);
        // sets joint ist (measured) values for the given arm
        bool setArmIst(int arm, ArmDataN& oArmData);
        // gets joint soll (commanded) values for the given arm
        bool getArmSoll(int arm, ArmDataN& oArmData);        
        // gets joint ist (measured) values for the given arm
        bool getArmIst(int arm, ArmDataN& oArmData);      
    
};

}    
#endif

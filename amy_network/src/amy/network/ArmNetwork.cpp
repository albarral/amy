/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/network/ArmNetwork.h"
#include "amy/network/DBArmStorage.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmNetwork::logger(Logger::getLogger("amy.network"));

// Constructor
ArmNetwork::ArmNetwork ()
{    
    benabled = false;
    pArmStorage = 0;
}

// Destructor
ArmNetwork::~ArmNetwork ()
{
    if (pArmStorage != 0)
    delete (pArmStorage);
}

bool ArmNetwork::init(int type)
{
    if (pArmStorage == 0)
    {
        if (type == ArmNetwork::eNETWORK_DB)
            pArmStorage = new DBArmStorage();    
    }
       
    if (pArmStorage != 0)    
        benabled = true;
    
    return benabled;
}


// sets soll (commanded) values for all joints
bool ArmNetwork::setArmSoll(int arm, ArmData& oArmData)
{
    if (benabled)
        return pArmStorage->storeArmSoll(arm, oArmData);
    else
        return false;
}


// sets ist (measured) values for all joints
bool ArmNetwork::setArmIst(int arm, ArmData& oArmData)
{
    if (benabled)
        return pArmStorage->storeArmIst(arm, oArmData);
    else
        return false;
}

// gets soll (commanded) values for all joints
bool ArmNetwork::getArmSoll(int arm, ArmData& oArmData)
{
    if (benabled)
        return pArmStorage->readArmSoll(arm, oArmData);
    else
        return false;
}

// gets ist (measured) values for all joints
bool ArmNetwork::getArmIst(int arm, ArmData& oArmData)
{
    if (benabled)
        return pArmStorage->readArmIst(arm, oArmData);
    else
        return false;
}

}

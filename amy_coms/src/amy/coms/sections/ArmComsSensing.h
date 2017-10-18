#ifndef __AMY_COMS_ARMCOMSSENSING_H
#define __AMY_COMS_ARMCOMSSENSING_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/core/ifaces/iArmInterface.h"
#include "talky/coms/CommandBlock.h"

namespace amy
{
// Class used to fetch arm sensor info.
// Info is returned in the form of talky command blocks (of arm topic).
class ArmComsSensing 
{    
private:
    static log4cxx::LoggerPtr logger;    
    
public:       
    // fetch arm sensor info through the arm interface
    static bool fetchArmInfo(iArmInterface* pArmInterface, talky::CommandBlock& oCommandBlock);
    
private:
    // fetch joints sensor info through the arm interface
    static bool fetchJointInfo(iArmInterface* pArmInterface, talky::CommandBlock& oCommandBlock);
};
}
#endif

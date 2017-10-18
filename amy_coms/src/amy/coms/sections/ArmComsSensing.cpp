/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/sections/ArmComsSensing.h"
#include "talky/Topics.h"
#include "talky/coms/Command.h"
#include "talky/topics/ArmTopic.h"

namespace amy
{
log4cxx::LoggerPtr ArmComsSensing::logger(log4cxx::Logger::getLogger("amy.coms"));


bool ArmComsSensing::fetchArmInfo(iArmInterface* pArmInterface, talky::CommandBlock& oCommandBlock)
{
    bool bret = true;

    // skip if no interface connection
    if (pArmInterface == 0)
    {
        LOG4CXX_ERROR(logger, "ArmComsSensing: can't fetch info, no arm interface connection");           
        return false;
    }

    // fetch joints info
    bret = fetchJointInfo(pArmInterface, oCommandBlock);

    return bret;
}

bool ArmComsSensing::fetchJointInfo(iArmInterface* pArmInterface, talky::CommandBlock& oCommandBlock)
{
    // skip if no interface connection
    if (pArmInterface == 0)
        return false;

    // all commands in this block have arm topic and joint category
    talky::Command oCommand;        
    oCommand.setTopic(talky::Topics::eTOPIC_ARM);
    oCommand.setCategory(talky::ArmTopic::eCAT_ARM_JOINT);
       
    // read commanded control values of all joints ...
    // and add them as commands to given command block
    // HS
    oCommand.setConcept(talky::ArmTopic::eJOINT_HS_POS);
    oCommand.setQuantity(pArmInterface->getHSControl());
    oCommandBlock.addCommand(oCommand);
    // VS
    oCommand.setConcept(talky::ArmTopic::eJOINT_VS_POS);
    oCommand.setQuantity(pArmInterface->getVSControl());
    oCommandBlock.addCommand(oCommand);
    // ELB
    oCommand.setConcept(talky::ArmTopic::eJOINT_ELB_POS);
    oCommand.setQuantity(pArmInterface->getELControl());
    oCommandBlock.addCommand(oCommand);
    // HWRI
    oCommand.setConcept(talky::ArmTopic::eJOINT_HWRI_POS);
    oCommand.setQuantity(pArmInterface->getHWControl());
    oCommandBlock.addCommand(oCommand);
    // VWRI
    oCommand.setConcept(talky::ArmTopic::eJOINT_VWRI_POS);
    oCommand.setQuantity(pArmInterface->getVWControl());
    oCommandBlock.addCommand(oCommand);

    return true;
}

}
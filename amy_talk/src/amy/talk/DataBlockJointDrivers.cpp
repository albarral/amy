/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/talk/DataBlockJointDrivers.h"
#include "talky/Topics.h"
#include "talky/coms/Command.h"
#include "talky/topics/ArmTopic.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr DataBlockJointDrivers::logger(Logger::getLogger("amy"));
    
DataBlockJointDrivers::DataBlockJointDrivers()
{
    // init data block
    topic = talky::Topics::eTOPIC_ARM;
    category = talky::ArmTopic::eCAT_ARM_JOINT;
    blockName = "drivers";
    // set required elements
    addElement(talky::ArmTopic::eJOINT_HS_STATE);
    addElement(talky::ArmTopic::eJOINT_VS_STATE);
    addElement(talky::ArmTopic::eJOINT_ELB_STATE);
    addElement(talky::ArmTopic::eJOINT_HWRI_STATE);
    addElement(talky::ArmTopic::eJOINT_VWRI_STATE);    
    resetData();
}

DataBlockJointDrivers::~DataBlockJointDrivers()
{
    reset();
}

void DataBlockJointDrivers::resetData()
{
    stateHS = 0;
    stateVS = 0;
    stateEL = 0;
    stateHW = 0;
    stateVW = 0;
}

bool DataBlockJointDrivers::isEqual(DataBlockJointDrivers& oArmJointInfo)
{
    return ((stateHS == oArmJointInfo.stateHS) &&
                (stateVS == oArmJointInfo.stateVS) &&
                (stateEL == oArmJointInfo.stateEL) &&
                (stateHW == oArmJointInfo.stateHW) &&
                (stateVW == oArmJointInfo.stateVW));
}

bool DataBlockJointDrivers::readBlock(talky::CommandBlock& oCommandBlock)
{
    // if block not compatible, skip
    if (!checkCompatibleBlock(oCommandBlock))
    {
        LOG4CXX_WARN(logger, "DataBlockJointDrivers: incompatible block");
        return false;
    }
        
    // analyze each command in the block
    for (talky::Command& oCommand : oCommandBlock.getListCommands())
    {
        int quantity = (int)oCommand.getQuantity();
        switch (oCommand.getConcept())
        {
            case talky::ArmTopic::eJOINT_HS_STATE:
                stateHS = quantity;
                break;
            case talky::ArmTopic::eJOINT_VS_STATE:
                stateVS = quantity;
                break;
            case talky::ArmTopic::eJOINT_ELB_STATE:
                stateEL = quantity;
                break;
            case talky::ArmTopic::eJOINT_HWRI_STATE:
                stateHW = quantity;
                break;
            case talky::ArmTopic::eJOINT_VWRI_STATE:
                stateVW = quantity;
                break;                
        }            
    }
    
    return true;
}

bool DataBlockJointDrivers::writeBlock(talky::CommandBlock& oCommandBlock)
{
    // all commands in the block have arm topic and joint category
    talky::Command oCommand;        
    oCommand.setTopic(topic);
    oCommand.setCategory(category);
       
    // create a talky command for each joint and add it to given command block
    // HS
    oCommand.setConcept(talky::ArmTopic::eJOINT_HS_STATE);
    oCommand.setQuantity(stateHS);
    oCommandBlock.addCommand(oCommand);
    // VS
    oCommand.setConcept(talky::ArmTopic::eJOINT_VS_STATE);
    oCommand.setQuantity(stateVS);
    oCommandBlock.addCommand(oCommand);
    // ELB
    oCommand.setConcept(talky::ArmTopic::eJOINT_ELB_STATE);
    oCommand.setQuantity(stateEL);
    oCommandBlock.addCommand(oCommand);
    // HWRI
    oCommand.setConcept(talky::ArmTopic::eJOINT_HWRI_STATE);
    oCommand.setQuantity(stateHW);
    oCommandBlock.addCommand(oCommand);
    // VWRI
    oCommand.setConcept(talky::ArmTopic::eJOINT_VWRI_STATE);
    oCommand.setQuantity(stateVW);
    oCommandBlock.addCommand(oCommand);

    return true;
}

std::string DataBlockJointDrivers::toString()
{
    std::string desc = "[DataBlockJointDrivers]: \n stateHS = " + std::to_string(stateHS) + 
                             "\n stateVS = " + std::to_string(stateVS) +
                             "\n stateEL = " + std::to_string(stateEL) +
                             "\n stateHW = " + std::to_string(stateHW) +
                             "\n stateVW = " + std::to_string(stateVW);
    
    return desc;
}

}

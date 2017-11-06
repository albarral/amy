/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/talk/DataBlockAxes.h"
#include "talky/Topics.h"
#include "talky/coms/Command.h"
#include "talky/topics/ArmTopic.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr DataBlockAxes::logger(Logger::getLogger("amy"));
    
DataBlockAxes::DataBlockAxes()
{
    // init data block
    topic = talky::Topics::eTOPIC_ARM;
    category = talky::ArmTopic::eCAT_ARM_AXIS;
    blockName = "axes";
    // set required elements
    addElement(talky::ArmTopic::eAXIS_PAN_POS);
    addElement(talky::ArmTopic::eAXIS_TILT_POS);
    addElement(talky::ArmTopic::eAXIS_RAD_POS);
    addElement(talky::ArmTopic::eAXIS_PAN_SPEED);
    addElement(talky::ArmTopic::eAXIS_TILT_SPEED);    
    resetData();
}

DataBlockAxes::~DataBlockAxes()
{
    reset();
}

void DataBlockAxes::resetData()
{
    pan = 0;
    tilt = 0;
    radius = 0;
    panSpeed = 0;
    tiltSpeed = 0;
}

bool DataBlockAxes::isEqual(DataBlockAxes& oArmJointInfo)
{
    return ((pan == oArmJointInfo.pan) &&
                (tilt == oArmJointInfo.tilt) &&
                (radius == oArmJointInfo.radius) &&
                (panSpeed == oArmJointInfo.panSpeed) &&
                (tiltSpeed == oArmJointInfo.tiltSpeed));
}

bool DataBlockAxes::readBlock(talky::CommandBlock& oCommandBlock)
{
    // if block not compatible, skip
    if (!checkCompatibleBlock(oCommandBlock))
    {
        LOG4CXX_WARN(logger, "DataBlockAxes: incompatible block");
        return false;
    }
        
    // analyze each command in the block
    for (talky::Command& oCommand : oCommandBlock.getListCommands())
    {
        float quantity = oCommand.getQuantity();
        switch (oCommand.getConcept())
        {
            case talky::ArmTopic::eAXIS_PAN_POS:
                pan = quantity;
                break;
            case talky::ArmTopic::eAXIS_TILT_POS:
                tilt = quantity;
                break;
            case talky::ArmTopic::eAXIS_RAD_POS:
                radius = quantity;
                break;
            case talky::ArmTopic::eAXIS_PAN_SPEED:
                panSpeed = quantity;
                break;
            case talky::ArmTopic::eAXIS_TILT_SPEED:
                tiltSpeed = quantity;
                break;                
        }            
    }
    
    return true;
}

bool DataBlockAxes::writeBlock(talky::CommandBlock& oCommandBlock)
{
    // all commands in the block have arm topic and joint category
    talky::Command oCommand;        
    oCommand.setTopic(topic);
    oCommand.setCategory(category);
       
    // create a talky command for each joint and add it to given command block
    // HS
    oCommand.setConcept(talky::ArmTopic::eAXIS_PAN_POS);
    oCommand.setQuantity(pan);
    oCommandBlock.addCommand(oCommand);
    // VS
    oCommand.setConcept(talky::ArmTopic::eAXIS_TILT_POS);
    oCommand.setQuantity(tilt);
    oCommandBlock.addCommand(oCommand);
    // ELB
    oCommand.setConcept(talky::ArmTopic::eAXIS_RAD_POS);
    oCommand.setQuantity(radius);
    oCommandBlock.addCommand(oCommand);
    // HWRI
    oCommand.setConcept(talky::ArmTopic::eAXIS_PAN_SPEED);
    oCommand.setQuantity(panSpeed);
    oCommandBlock.addCommand(oCommand);
    // VWRI
    oCommand.setConcept(talky::ArmTopic::eAXIS_TILT_SPEED);
    oCommand.setQuantity(tiltSpeed);
    oCommandBlock.addCommand(oCommand);

    return true;
}

std::string DataBlockAxes::toString()
{
    std::string desc = "[DataBlockAxes]: \n posHS = " + std::to_string(pan) + 
                             "\n posVS = " + std::to_string(tilt) +
                             "\n posEL = " + std::to_string(radius) +
                             "\n posHW = " + std::to_string(panSpeed) +
                             "\n posVW = " + std::to_string(tiltSpeed);
    
    return desc;
}

}

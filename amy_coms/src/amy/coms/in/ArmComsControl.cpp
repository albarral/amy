/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/coms/in/ArmComsControl.h"
#include "talky/topics/ArmTopic.h"

namespace amy
{
log4cxx::LoggerPtr ArmComsControl::logger(log4cxx::Logger::getLogger("amy.coms"));

ArmComsControl::ArmComsControl()
{    
    pArmBus = 0;
}

void ArmComsControl::connect2Arm(ArmBus* pArmBus)
{
    this->pArmBus = pArmBus;
}

bool ArmComsControl::processCommand(talky::Command& oCommand, ComsData& oComsData)
{
    bool bret = true;

    // skip if no interface connection
    if (pArmBus == 0)
    {
        LOG4CXX_ERROR(logger, "ArmComsControl: can't process command, no connection to arm interface");           
        return false;
    }

    switch (oCommand.getCategory())
    {
        case talky::ArmTopic::eCAT_ARM_JOINT:
            bret = processJointCommand(oCommand);
            break;

        case talky::ArmTopic::eCAT_ARM_AXIS:
            bret = processAxisCommand(oCommand);
            break;

        case talky::ArmTopic::eCAT_ARM_CYCLIC:
            bret = processCyclicCommand(oCommand);
            break;

        case talky::ArmTopic::eCAT_ARM_EXTRA:
            bret = processExtraCommand(oCommand, oComsData);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ArmComsControl: can't process command, untreated category " << oCommand.getCategory());                        
    }                
    return bret;
}

bool ArmComsControl::processJointCommand(talky::Command& oCommand)
{
    bool bret = true;
    float quantity = oCommand.getQuantity();

    switch (oCommand.getConcept())
    {
        case talky::ArmTopic::eJOINT_HS_POS:
            LOG4CXX_INFO(logger, "> set HS " << quantity);                        
            pArmBus->getBusHS().getCO_JOINT_ANGLE().request(quantity);
            break;
            
        case talky::ArmTopic::eJOINT_VS_POS:
            LOG4CXX_INFO(logger, "> set VS " << quantity);                        
            pArmBus->getBusVS().getCO_JOINT_ANGLE().request(quantity);
            break;

        case talky::ArmTopic::eJOINT_ELB_POS:
            LOG4CXX_INFO(logger, "> set ELB " << quantity);                        
            pArmBus->getBusEL().getCO_JOINT_ANGLE().request(quantity);
            break;

        case talky::ArmTopic::eJOINT_HWRI_POS:
            LOG4CXX_INFO(logger, "> set HW " << quantity);                        
            pArmBus->getBusHW().getCO_JOINT_ANGLE().request(quantity);
            break;

        case talky::ArmTopic::eJOINT_VWRI_POS:
            LOG4CXX_INFO(logger, "> set VW " << quantity);                        
            pArmBus->getBusVW().getCO_JOINT_ANGLE().request(quantity);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ArmComsControl: can't process command, untreated joint concept " << oCommand.getConcept());           
    }    
    return bret;
}

bool ArmComsControl::processAxisCommand(talky::Command& oCommand)
{
    bool bret = true;
    float quantity = oCommand.getQuantity();
    
    switch (oCommand.getConcept())
    {
        case talky::ArmTopic::eAXIS_PAN_POS:
            LOG4CXX_INFO(logger, "> move pan " << quantity);                        
            pArmBus->getPanBus().getCO_AXIS_POS().request(quantity);
            break;
            
        case talky::ArmTopic::eAXIS_TILT_POS:
            LOG4CXX_INFO(logger, "> move tilt " << quantity);                        
            pArmBus->getTiltBus().getCO_AXIS_POS().request(quantity);
            break;

        case talky::ArmTopic::eAXIS_RAD_POS:
            LOG4CXX_INFO(logger, "> move radius " << quantity);                        
            pArmBus->getRadialBus().getCO_AXIS_POS().request(quantity);
            break;

        case talky::ArmTopic::eAXIS_PAN_SPEED:
            LOG4CXX_INFO(logger, "> pan speed " << quantity);                        
            pArmBus->getPanBus().getCO_AXIS_SPEED().request(quantity);
            break;
            
        case talky::ArmTopic::eAXIS_TILT_SPEED:
            LOG4CXX_INFO(logger, "> tilt speed " << quantity);                        
           pArmBus->getTiltBus().getCO_AXIS_SPEED().request(quantity);
            break;

        case talky::ArmTopic::eAXIS_RAD_SPEED:
            LOG4CXX_INFO(logger, "> rad speed " << quantity);                        
            pArmBus->getRadialBus().getCO_AXIS_SPEED().request(quantity);
            break;
            
        default:
            bret = false;
            LOG4CXX_WARN(logger, "ArmComsControl: can't process command, untreated axis concept " << oCommand.getConcept());           
    }    
    return bret;
}

bool ArmComsControl::processCyclicCommand(talky::Command& oCommand)
{
    bool bret = true;
    float quantity = oCommand.getQuantity();
    bool byes;

    switch (oCommand.getConcept())
    {
        // FRONTAL CYCLER
        case talky::ArmTopic::eCYCLIC_FRONT1_FREQ:
            LOG4CXX_INFO(logger, "> set front1 freq " << quantity);                        
            pArmBus->getFrontalCyclerBus().getCO_CYCLER_FREQ1().request(quantity);
            break;
            
        case talky::ArmTopic::eCYCLIC_FRONT1_AMP:
            LOG4CXX_INFO(logger, "> set front1 amplitude " << quantity);                        
            pArmBus->getFrontalCyclerBus().getCO_CYCLER_AMPLITUDE1().request(quantity);
            break;

        case talky::ArmTopic::eCYCLIC_FRONT1_ANGLE:
            LOG4CXX_INFO(logger, "> set front1 angle ");                        
            pArmBus->getFrontalCyclerBus().getCO_CYCLER_ANGLE1().request(quantity);
            break;

        case talky::ArmTopic::eCYCLIC_FRONT2_FREQ:
            LOG4CXX_INFO(logger, "> set front2 freq " << quantity);                        
            pArmBus->getFrontalCyclerBus().getCO_CYCLER_FREQ2().request(quantity);
            break;
            
        case talky::ArmTopic::eCYCLIC_FRONT2_AMP:
            LOG4CXX_INFO(logger, "> set front2 amplitude " << quantity);                        
            pArmBus->getFrontalCyclerBus().getCO_CYCLER_AMPLITUDE2().request(quantity);
            break;

        case talky::ArmTopic::eCYCLIC_FRONT2_ANGLE:
            LOG4CXX_INFO(logger, "> set front2 angle ");                        
            pArmBus->getFrontalCyclerBus().getCO_CYCLER_ANGLE2().request(quantity);
            break;

        case talky::ArmTopic::eCYCLIC_FRONT_START:
            LOG4CXX_INFO(logger, "> front start ");                        
            pArmBus->getFrontalCyclerBus().getCO_CYCLER_ACTION().request(true);
            break;

        case talky::ArmTopic::eCYCLIC_FRONT_STOP:
            LOG4CXX_INFO(logger, "> front stop ");                        
            pArmBus->getFrontalCyclerBus().getCO_CYCLER_ACTION().request(false);
            break;


        default:
            bret = false;
            LOG4CXX_WARN(logger, "ArmComsControl: can't process command, untreated cyclic concept " << oCommand.getConcept());           
    }    
    return bret;
}

bool ArmComsControl::processExtraCommand(talky::Command& oCommand, ComsData& oComsData)
{
    bool bret = true;
    float quantity = oCommand.getQuantity();
    
    switch (oCommand.getConcept())
    {
        case talky::ArmTopic::eEXTRA_ARM_STOP:
            LOG4CXX_INFO(logger, "> arm stop ");                        
            toDoCommand(quantity);
            break;
            
        case talky::ArmTopic::eEXTRA_KEEP_TILT:
            LOG4CXX_INFO(logger, "> keep tilt " << quantity);                        
            pArmBus->getCO_KEEP_TILT().request((int)quantity);
            break;
            
        case talky::ArmTopic::eEXTRA_AMY_END:
            LOG4CXX_INFO(logger, "> end emy");  
            oComsData.addSpecialAction(ComsData::eACTION_AMY_END);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ArmComsControl: can't process command, untreated extra concept " << oCommand.getConcept());           
    }    
    return bret;
}


void ArmComsControl::toDoCommand(float value)
{
    // nothing done
    // dummy method for to do commands
    LOG4CXX_INFO(logger, "> to do");                        
}

}
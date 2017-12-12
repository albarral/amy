/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/coms/in/ComsInArmControl.h"
#include "talky/topics/ArmTopic.h"

namespace amy
{
log4cxx::LoggerPtr ComsInArmControl::logger(log4cxx::Logger::getLogger("amy.coms"));

ComsInArmControl::ComsInArmControl()
{    
    pArmBus = 0;
}

void ComsInArmControl::connect2Arm(ArmBus* pArmBus)
{
    this->pArmBus = pArmBus;
}


bool ComsInArmControl::processCommand(talky::Command& oCommand)
{
    bool bret = true;

    // skip if no interface connection
    if (pArmBus == 0)
    {
        LOG4CXX_ERROR(logger, "ComsInArmControl: can't process command, no bus connection");           
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
            bret = processExtraCommand(oCommand);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ComsInArmControl: can't process command, untreated category " << oCommand.getCategory());                        
    }                
    return bret;
}

bool ComsInArmControl::processJointCommand(talky::Command& oCommand)
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
            LOG4CXX_WARN(logger, "ComsInArmControl: can't process command, untreated joint concept " << oCommand.getConcept());           
    }    
    return bret;
}

bool ComsInArmControl::processAxisCommand(talky::Command& oCommand)
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
            LOG4CXX_WARN(logger, "ComsInArmControl: can't process command, untreated axis concept " << oCommand.getConcept());           
    }    
    return bret;
}

bool ComsInArmControl::processCyclicCommand(talky::Command& oCommand)
{
    bool bret = true;
    float quantity = oCommand.getQuantity();
    bool bgo;

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
            LOG4CXX_INFO(logger, "> set front1 angle " << quantity);                        
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
            LOG4CXX_INFO(logger, "> set front2 angle " << quantity);                        
            pArmBus->getFrontalCyclerBus().getCO_CYCLER_ANGLE2().request(quantity);
            break;

        case talky::ArmTopic::eCYCLIC_FRONT_PHASE:
            LOG4CXX_INFO(logger, "> set front phase " << quantity);                        
            pArmBus->getFrontalCyclerBus().getCO_CYCLER_PHASE().request((int)quantity);
            break;

        case talky::ArmTopic::eCYCLIC_FRONT_ACTION:
            bgo = ((int)quantity != 0); 
            LOG4CXX_INFO(logger, "> front action " << bgo);                        
            pArmBus->getFrontalCyclerBus().getCO_CYCLER_ACTION().request(bgo);
            break;


        default:
            bret = false;
            LOG4CXX_WARN(logger, "ComsInArmControl: can't process command, untreated cyclic concept " << oCommand.getConcept());           
    }    
    return bret;
}

bool ComsInArmControl::processExtraCommand(talky::Command& oCommand)
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
            oQueueSpecialActions.add(ComsInArmControl::eACTION_AMY_END);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ComsInArmControl: can't process command, untreated extra concept " << oCommand.getConcept());           
    }    
    return bret;
}


void ComsInArmControl::toDoCommand(float value)
{
    // nothing done
    // dummy method for to do commands
    LOG4CXX_INFO(logger, "> to do");                        
}

}
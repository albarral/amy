/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/coms/sections/ArmComsControl.h"
#include "talky/topics/ArmTopic.h"

namespace amy
{
log4cxx::LoggerPtr ArmComsControl::logger(log4cxx::Logger::getLogger("amy.coms"));

ArmComsControl::ArmComsControl()
{    
    pArmInterface = 0;
    bamyEndRequested = false;
}

void ArmComsControl::connect2Arm(iArmInterface* pArmInterface)
{
    this->pArmInterface = pArmInterface;
}

bool ArmComsControl::processCommand(talky::Command& oCommand)
{
    bool bret = true;

    // skip if no interface connection
    if (pArmInterface == 0)
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
            bret = processExtraCommand(oCommand);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ArmComsControl: untreated category " << oCommand.getCategory());                        
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
            pArmInterface->moveHS(quantity);
            break;
            
        case talky::ArmTopic::eJOINT_VS_POS:
            LOG4CXX_INFO(logger, "> set VS " << quantity);                        
            pArmInterface->moveVS(quantity);
            break;

        case talky::ArmTopic::eJOINT_ELB_POS:
            LOG4CXX_INFO(logger, "> set ELB " << quantity);                        
            pArmInterface->moveEL(quantity);
            break;

        case talky::ArmTopic::eJOINT_HWRI_POS:
            LOG4CXX_INFO(logger, "> set HW " << quantity);                        
            pArmInterface->moveHW(quantity);
            break;

        case talky::ArmTopic::eJOINT_VWRI_POS:
            LOG4CXX_INFO(logger, "> set VW " << quantity);                        
            pArmInterface->moveVW(quantity);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ArmComsControl: untreated joint concept " << oCommand.getConcept());           
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
            pArmInterface->movePan(quantity);
            break;
            
        case talky::ArmTopic::eAXIS_TILT_POS:
            LOG4CXX_INFO(logger, "> move tilt " << quantity);                        
            pArmInterface->moveTilt(quantity);
            break;

        case talky::ArmTopic::eAXIS_RAD_POS:
            LOG4CXX_INFO(logger, "> move radius " << quantity);                        
            pArmInterface->extend(quantity);
            break;

        case talky::ArmTopic::eAXIS_PAN_SPEED:
            LOG4CXX_INFO(logger, "> pan speed " << quantity);                        
            pArmInterface->panSpeed(quantity);
            break;
            
        case talky::ArmTopic::eAXIS_TILT_SPEED:
            LOG4CXX_INFO(logger, "> tilt speed " << quantity);                        
           pArmInterface->tiltSpeed(quantity);
            break;

        case talky::ArmTopic::eAXIS_RAD_SPEED:
            LOG4CXX_INFO(logger, "> rad speed " << quantity);                        
            pArmInterface->radialSpeed(quantity);
            break;
            
        default:
            bret = false;
            LOG4CXX_WARN(logger, "ArmComsControl: untreated axis concept " << oCommand.getConcept());           
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
        case talky::ArmTopic::eCYCLIC_FRONT_FREQ:
            LOG4CXX_INFO(logger, "> set front freq " << quantity);                        
            pArmInterface->frontFrequency(quantity);
            break;
            
        case talky::ArmTopic::eCYCLIC_FRONT_AMP:
            LOG4CXX_INFO(logger, "> set front amplitude " << quantity);                        
            pArmInterface->frontAmplitude(quantity);
            break;

        case talky::ArmTopic::eCYCLIC_FRONT_ANGLE:
            LOG4CXX_INFO(logger, "> set front angle ");                        
            pArmInterface->frontAngle(quantity);
            break;

        case talky::ArmTopic::eCYCLIC_FRONT_START:
            LOG4CXX_INFO(logger, "> front start ");                        
            pArmInterface->frontAction(true);
            break;

        case talky::ArmTopic::eCYCLIC_FRONT_STOP:
            LOG4CXX_INFO(logger, "> front stop ");                        
             pArmInterface->frontAction(false);
            break;

       // ARM MOVER            
        case talky::ArmTopic::eCYCLIC_MOVER_LAUNCH:
            LOG4CXX_INFO(logger, "> launch move " << (int)quantity);                        
            pArmInterface->launchMove((int)quantity);
            break;
            
        case talky::ArmTopic::eCYCLIC_MOVER_STOP:
            LOG4CXX_INFO(logger, "> stop move");                        
            pArmInterface->stopMove();
            break;

        case talky::ArmTopic::eCYCLIC_MOVER_TURN:
            LOG4CXX_INFO(logger, "> turn move " << (int)quantity);                        
            pArmInterface->turnMove((int)quantity);
            break;

        case talky::ArmTopic::eCYCLIC_MOVER_WIDER:
            byes = (quantity == 1.0);
            {
                std::string text = (byes ? "> move wider" : "> move narrower");
                LOG4CXX_INFO(logger, text);                        
            }
            pArmInterface->moveWider(byes);
            break;

        case talky::ArmTopic::eCYCLIC_MOVER_TALLER:
            byes = (quantity == 1.0);
            {
                std::string text = (byes ? "> move taller" : "> move shorter");
                LOG4CXX_INFO(logger, text);                        
            }
            pArmInterface->moveTaller(byes);
            break;

        case talky::ArmTopic::eCYCLIC_MOVER_FASTER:
            byes = (quantity == 1.0);
            {
                std::string text = (byes ? "> move faster" : "> move slower");
                LOG4CXX_INFO(logger, text);                        
            }
            pArmInterface->moveFaster(byes);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ArmComsControl: untreated cyclic concept " << oCommand.getConcept());           
    }    
    return bret;
}

bool ArmComsControl::processExtraCommand(talky::Command& oCommand)
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
            pArmInterface->keepTilt((int)quantity);
            break;
            
        case talky::ArmTopic::eEXTRA_AMY_END:
            LOG4CXX_INFO(logger, "> end emy");                        
            bamyEndRequested = true;    
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ArmComsControl: untreated extra concept " << oCommand.getConcept());           
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
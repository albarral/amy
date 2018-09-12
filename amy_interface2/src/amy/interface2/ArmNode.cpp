/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/ArmNode.h"
#include "tron/topics/NodeSection.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/channels/ExtraSection.h"

namespace amy
{    

ArmNode2::ArmNode2() : tron::Node(tron::RobotNodes::eNODE_ARM)
{
    oSectionsMap.addCode(eSECTION_JOINTS, SECTION_JOINTS);
    oSectionsMap.addCode(eSECTION_AXES, SECTION_AXES);
    oSectionsMap.addCode(eSECTION_CYCLER1, SECTION_CYCLER1);
    oSectionsMap.addCode(eSECTION_CYCLER2, SECTION_CYCLER2);
    oSectionsMap.addCode(eSECTION_EXTRA, tron::ExtraSection::EXTRA_SECTION);
    
    setJointsSection();
    setAxesSection();
    setCyclerSection(eSECTION_CYCLER1);
    setCyclerSection(eSECTION_CYCLER2);

    tron::ExtraSection oExtraSection(eSECTION_EXTRA);
    listNodeSections.push_back(oExtraSection);    
}

void ArmNode2::setJointsSection()
{
    tron::NodeSection oJointsSection(eSECTION_JOINTS);
    
    oJointsSection.addChannel(eJOINTS_HS, JOINTS_HS);
    oJointsSection.addChannel(eJOINTS_VS, JOINTS_VS);                         
    oJointsSection.addChannel(eJOINTS_ELB, JOINTS_ELB);                      
    oJointsSection.addChannel(eJOINTS_HWRI, JOINTS_HWRI);                   
    oJointsSection.addChannel(eJOINTS_VWRI, JOINTS_VWRI);   
    
    listNodeSections.push_back(oJointsSection);    
}

void ArmNode2::setAxesSection()
{
    tron::NodeSection oAxesSection(eSECTION_AXES);
    
    oAxesSection.addChannel(eAXES_PAN, AXES_PAN);
    oAxesSection.addChannel(eAXES_TILT, AXES_TILT);                         
    oAxesSection.addChannel(eAXES_RAD, AXES_RAD);                      
    oAxesSection.addChannel(eAXES_PAN_SPEED, AXES_PAN_SPEED);                   
    oAxesSection.addChannel(eAXES_TILT_SPEED, AXES_TILT_SPEED);                        
    oAxesSection.addChannel(eAXES_RAD_SPEED, AXES_RAD_SPEED);                        
    oAxesSection.addChannel(eAXES_KEEP_TILT, AXES_KEEP_TILT);                         
    
    listNodeSections.push_back(oAxesSection);        
}

void ArmNode2::setCyclerSection(int section)
{
    tron::NodeSection oCyclerSection(section);
    
    oCyclerSection.addChannel(eCYCLER_MAIN_FREQ, CYCLER_MAIN_FREQ);
    oCyclerSection.addChannel(eCYCLER_MAIN_AMP, CYCLER_MAIN_AMP);                         
    oCyclerSection.addChannel(eCYCLER_MAIN_ANGLE, CYCLER_MAIN_ANGLE);                      
    oCyclerSection.addChannel(eCYCLER_MAIN_PHASE, CYCLER_MAIN_PHASE);                   
    oCyclerSection.addChannel(eCYCLER_SEC_FREQ, CYCLER_SEC_FREQ);
    oCyclerSection.addChannel(eCYCLER_SEC_AMP, CYCLER_SEC_AMP);                         
    oCyclerSection.addChannel(eCYCLER_SEC_ANGLE, CYCLER_SEC_ANGLE);                      
    oCyclerSection.addChannel(eCYCLER_SEC_PHASE, CYCLER_SEC_PHASE);                   
    oCyclerSection.addChannel(eCYCLER_ACTION, CYCLER_ACTION);                        
    
    listNodeSections.push_back(oCyclerSection);            
}

std::string ArmNode2::toString()
{
    return "ArmNode\n" + tron::Node::toString();
}
}
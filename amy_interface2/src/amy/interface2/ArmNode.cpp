/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/ArmNode.h"
#include "amy/interface2/channels/JointsSection.h"
#include "amy/interface2/channels/AxesSection.h"
#include "amy/interface2/channels/CyclerSection.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/channels/ExtraSection.h"

namespace amy
{    

ArmNode2::ArmNode2() : tron::Node(tron::RobotNodes::eNODE_ARM)
{
    oSectionsMap.addCode(ArmNode2::eSECTION_JOINTS, ArmNode2::SECTION_JOINTS);
    oSectionsMap.addCode(ArmNode2::eSECTION_AXES, ArmNode2::SECTION_AXES);
    oSectionsMap.addCode(ArmNode2::eSECTION_CYCLER1, ArmNode2::SECTION_CYCLER1);
    oSectionsMap.addCode(ArmNode2::eSECTION_CYCLER2, ArmNode2::SECTION_CYCLER2);
    oSectionsMap.addCode(ArmNode2::eSECTION_EXTRA, tron::ExtraSection::EXTRA_SECTION);
    
    JointsSection oJointsSection;
    listNodeSections.push_back(oJointsSection);
    AxesSection oAxesSection;
    listNodeSections.push_back(oAxesSection);
    CyclerSection oCyclerSection;
    listNodeSections.push_back(oCyclerSection);
    listNodeSections.push_back(oCyclerSection);
    tron::ExtraSection oExtraSection(ArmNode2::eSECTION_EXTRA);
    listNodeSections.push_back(oExtraSection);    
}

std::string ArmNode2::toString()
{
    return "ArmNode\n" + tron::Node::toString();
}
}
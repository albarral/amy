/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/interface2/ArmNode.h"
#include "amy/interface2/channels/JointsSection.h"
#include "amy/interface2/channels/AxesSection.h"
#include "amy/interface2/channels/CyclerSection.h"
#include "tron/topics/RobotNodes.h"
#include "tron/topics/ExtraSection.h"

namespace amy
{    

ArmNode2::ArmNode2() : tron::Node(tron::RobotNodes::eNODE_ARM)
{
    oSectionsMap.addCode(ArmNode2::eSECTION_JOINTS, ArmNode2::SECTION_JOINTS);
    oSectionsMap.addCode(ArmNode2::eSECTION_AXES, ArmNode2::SECTION_AXES);
    oSectionsMap.addCode(ArmNode2::eSECTION_CYCLER1, ArmNode2::SECTION_CYCLER1);
    oSectionsMap.addCode(ArmNode2::eSECTION_CYCLER2, ArmNode2::SECTION_CYCLER2);
    oSectionsMap.addCode(ArmNode2::eSECTION_EXTRA, tron::ExtraSection::EXTRA_SECTION);
}

tron::NodeSection* ArmNode2::getSection(int sectionCode)
{
    switch (sectionCode)
    {
        case ArmNode2::eSECTION_JOINTS:
            return new JointsSection();

        case ArmNode2::eSECTION_AXES:
            return new AxesSection();
            
        case ArmNode2::eSECTION_CYCLER1:
        case ArmNode2::eSECTION_CYCLER2:
            return new CyclerSection();
        
        case ArmNode2::eSECTION_EXTRA: 
            return new tron::ExtraSection();

        default:
            return nullptr;
    }            
}


bool ArmNode2::buildTopic(tron::Topic & oTopic)
{
    tron::RobotNodes oRobotNodes;
    // get node name
    oTopic.setNodeName(oRobotNodes.getName4Node(oTopic.getNode()));
    // get section name
    oTopic.setSectionName(getName4Section(oTopic.getSection()));    
    // get channel name
    tron::NodeSection* pNodeSection = getSection(oTopic.getSection());
    if (pNodeSection != nullptr)
    {
        oTopic.setChannelName(pNodeSection->getName4Channel(oTopic.getChannel())); 
        oTopic.build();
        delete (pNodeSection);
        
        return oTopic.isBuilt();
    }
    else
        return false;
}


std::string ArmNode2::toString()
{
    return "ArmNode\n" + tron::Node::toString();
}
}
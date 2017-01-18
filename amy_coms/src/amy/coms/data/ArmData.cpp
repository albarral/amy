/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/data/ArmData.h"
#include "amy/utils/StringUtil.h"

namespace amy
{
void ArmData::reset()
{
    sollHS = 0;
    sollVS = 0;
    sollEL = 0;
    sollHW = 0;
    sollVW = 0;
    
    istHS = 0;
    istVS = 0;
    istEL = 0;
    istHW = 0;
    istVW = 0;
}


bool ArmData::sameSollValues(ArmData& oArmData)
{
    return ((sollHS == oArmData.sollHS) &&
                (sollVS == oArmData.sollVS) &&
                (sollEL == oArmData.sollEL) &&
                (sollHW == oArmData.sollHW) &&
                (sollVW == oArmData.sollVW));
}


bool ArmData::sameIstValues(ArmData& oArmData)
{
    return ((istHS == oArmData.istHS) &&
                (istVS == oArmData.istVS) &&
                (istEL == oArmData.istEL) &&
                (istHW == oArmData.istHW) &&
                (istVW == oArmData.istVW));
}

std::string ArmData::createSollMessage()
{
    // build the soll message writing each soll value in a different line
    std::string separator = "*";
    
    std::string message = std::to_string(sollHS) + separator 
                                  + std::to_string(sollVS) + separator 
                                  + std::to_string(sollEL) + separator 
                                  + std::to_string(sollHW) + separator 
                                  + std::to_string(sollVW) + "\n";
    
    return message;
}

bool ArmData::processSollMessage(std::string message)
{
    bool bvalid;
    std::string separator = "*";

    // split the soll message in tokens, where each token is a soll value
    std::vector<std::string> listTokens = StringUtil::split(message, separator); 

    // then transform each token (soll value in textual form) to its numeric value
    if (listTokens.size() == ArmData::numJoints)
    {             
        bvalid = StringUtil::convert2Float(listTokens.at(0), sollHS);
        if (bvalid)
            bvalid = StringUtil::convert2Float(listTokens.at(1), sollVS);
        if (bvalid)
            bvalid = StringUtil::convert2Float(listTokens.at(2), sollEL);
        if (bvalid)
            bvalid = StringUtil::convert2Float(listTokens.at(3), sollHW);
        if (bvalid)
            bvalid = StringUtil::convert2Float(listTokens.at(4), sollVW);
    }
    
    return bvalid;
}

std::string ArmData::toString()
{
    std::string desc = "[ArmData]: \n sollHS = " + std::to_string(sollHS) + 
                             "\n sollVS = " + std::to_string(sollVS) +
                             "\n sollEL = " + std::to_string(sollEL) +
                             "\n sollHW = " + std::to_string(sollHW) +
                             "\n sollVW = " + std::to_string(sollVW) +
                             "\n istHS = " + std::to_string(istHS) + 
                             "\n istVS = " + std::to_string(istVS) + 
                             "\n istEL = " + std::to_string(istEL) + 
                             "\n istHW = " + std::to_string(istHW) + 
                             "\n istVW = " + std::to_string(istVW);
    
    return desc;
}

}

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/network/ArmData.h"

namespace amy
{
void ArmData::reset()
{
    soll1 = 0;
    soll2 = 0;
    soll3 = 0;
    soll4 = 0;
    soll5 = 0;
    
    ist1 = 0;
    ist2 = 0;
    ist3 = 0;
    ist4 = 0;
    ist5 = 0;
}

std::string ArmData::toString()
{
    std::string desc = "[ArmData]: \n soll1 = " + std::to_string(soll1) + 
                             "\n soll2 = " + std::to_string(soll2) +
                             "\n soll3 = " + std::to_string(soll3) +
                             "\n soll4 = " + std::to_string(soll4) +
                             "\n soll5 = " + std::to_string(soll5) +
                             "\n ist1 = " + std::to_string(ist1) + 
                             "\n ist2 = " + std::to_string(ist2) + 
                             "\n ist3 = " + std::to_string(ist3) + 
                             "\n ist4 = " + std::to_string(ist4) + 
                             "\n ist5 = " + std::to_string(ist5);
    
    return desc;
}

}

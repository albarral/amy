/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cstdlib>  // for getenv

#include "amy/coms/AmyComsConfig.h"

namespace amy
{    
// Constructor
AmyComsConfig::AmyComsConfig()
{    
    // coms file located in home folder
    char* pVar = getenv("HOME");    
    if (pVar!=NULL)
    {
        std::string home(pVar);
        // file for client server coms        
        comsFilename1 = home + "/coms/amy_in.txt";
        // file for publish subscribe coms
        comsFilename2 = home + "/coms/amy_pub.txt";
    }
}

std::string AmyComsConfig::getComsFolder()
{
    // coms file located in home folder
    char* pVar = getenv("HOME");    
    if (pVar!=NULL)
    {
        std::string home(pVar);
        return home + "/coms";
    }
}

}


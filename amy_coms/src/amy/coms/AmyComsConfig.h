#ifndef __AMY_COMS_CONFIG_H
#define __AMY_COMS_CONFIG_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
class AmyComsConfig 
{
    private:                
        std::string comsFilename1;     // name of file used for client-server communications
        std::string comsFilename2;     // name of file used for publish-subscribe communications
        
    public:
        AmyComsConfig();
        //~AmyComsConfig();
                
        std::string getComsFilename1() {return comsFilename1;}        
        std::string getComsFilename2() {return comsFilename2;}        
};

}

#endif

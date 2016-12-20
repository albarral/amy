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
        std::string comsFilename;     // name of file used for client-server communication
        
    public:
        AmyComsConfig();
        //~AmyComsConfig();
                
        std::string getComsFilename() {return comsFilename;}        
};

}

#endif

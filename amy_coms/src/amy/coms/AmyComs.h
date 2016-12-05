#ifndef __AMY_COMS_CLIENT_H
#define __AMY_COMS_CLIENT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "amy/coms/AmyCommand.h"
#include "amy/utils/FileWriter.h"

namespace amy
{
class AmyComs
{    
private:
    std::string filename;
    AmyCommand oAmyCommand;
    FileWriter oFile;
    
public:
    AmyComs();

    void movePan(float value);
//    void moveTilt(float value);
//    void moveRadius(float value);
    
private:
    // send textual command
    void sendCommand(std::string text);
};
}
#endif

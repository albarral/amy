/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cstdlib>  // for getenv
#include <iostream>

#include "amy/coms/file/AmyFileClient.h"

namespace amy
{

AmyFileClient::AmyFileClient()
{    
    char* pVar = getenv("HOME");
    
    if (pVar!=NULL)
    {
        std::string home(pVar);
        filename = home + "/coms/amy_in.txt";
        oFile.open(filename);   // no append mode
    }
}

void AmyFileClient::sendCommand()
{
    std::cout << "command: " << oAmyCommand.getText() << std::endl;
    if (oFile.open(filename))        
    {
        oFile.goTop();
        oFile.writeFlush(oAmyCommand.getText());
    }
}


}
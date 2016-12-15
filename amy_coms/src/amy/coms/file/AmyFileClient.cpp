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
        oFileWriter.open(filename);   // no append mode
    }
}

AmyFileClient::~AmyFileClient()
{
    oFileWriter.close();    
}

void AmyFileClient::sendCommand()
{
    std::cout << "command: " << oAmyCommand.getText() << std::endl;
    if (oFileWriter.isOpen())        
    {
        oFileWriter.goTop();
        oFileWriter.writeFlush(oAmyCommand.getText());
    }
}


}
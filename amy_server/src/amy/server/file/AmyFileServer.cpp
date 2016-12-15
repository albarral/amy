/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <cstdlib>  // for getenv
#include <iostream>

#include "amy/server/file/AmyFileServer.h"


namespace amy
{
log4cxx::LoggerPtr AmyFileServer::logger(log4cxx::Logger::getLogger("amy.server"));

AmyFileServer::AmyFileServer()
{    
    char* pVar = getenv("HOME");
    
    if (pVar!=NULL)
    {
        std::string home(pVar);
        filename = home + "/coms/amy_in.txt";
        oFileReader.open(filename);   
    }
}

AmyFileServer::~AmyFileServer()
{
    oFileReader.close();    
}

bool AmyFileServer::readCommand()
{
    bool brequest = false;  // default no request received
    
    if (oFileReader.isOpen())        
    {
        // read file
        std::string text = oFileReader.readLine();

        // if request received, interpret it
        if (!text.empty())
        {
            brequest = true;
            bvalid = oAmyCommand.interpret(text);
            LOG4CXX_INFO(logger, "AmyFileServer: received command " << oAmyCommand.getDescription());
        }
    }
    else
    {
        LOG4CXX_ERROR(logger, "AmyFileServer: could not open coms file " << filename);
    }
    
    return brequest;
}

void AmyFileServer::processCommand()
{
    LOG4CXX_ERROR(logger, "AmyFileServer.processCommand(): TO DO ...");
}

}
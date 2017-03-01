/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <iostream>

#include "amy/coms/file/AmyFileServer.h"
#include "amy/coms/AmyComsConfig.h"

namespace amy
{
//log4cxx::LoggerPtr AmyFileServer::logger(log4cxx::Logger::getLogger("amy.server"));

AmyFileServer::AmyFileServer()
{    
    // get coms file name
    AmyComsConfig oAmyComsConfig;    
    filename = oAmyComsConfig.getComsFilename1();
    // open coms file for reading & writing
    if (!filename.empty())
    {
        oFileReader.open(filename);   
        oFileWriter.open(filename);   
    }
}

AmyFileServer::~AmyFileServer()
{
    oFileReader.close();
    oFileWriter.close();    
}

bool AmyFileServer::readCommand()
{
    bool brequest = false;  // default no request received

    if (oFileReader.isOpen())        
    {
        // read file from top
        oFileReader.readFromTop();
        //LOG4CXX_INFO(logger, "AmyFileServer: read pos " << oFileReader.getPos());
        text = oFileReader.readLine();
        
        // and clear it
        oFileWriter.writeFromTop();
        oFileWriter.writeFlush("\n");

        // if request received, interpret it
        if (!text.empty())
            brequest = true;
    }
    else
    {
        LOG4CXX_ERROR(logger, "AmyFileServer: could not open coms file " << filename);
    }
    
    return brequest;
}


}
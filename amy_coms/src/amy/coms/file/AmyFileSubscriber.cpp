/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/coms/file/AmyFileSubscriber.h"
#include "amy/coms/AmyComsConfig.h"

namespace amy
{
log4cxx::LoggerPtr AmyFileSubscriber::logger(log4cxx::Logger::getLogger("amy.subscriber"));

AmyFileSubscriber::AmyFileSubscriber()
{    
    // get coms file name
    AmyComsConfig oAmyComsConfig;    
    filename = oAmyComsConfig.getComsFilename2();
}

AmyFileSubscriber::~AmyFileSubscriber()
{
    oFileReader.close();
}

void AmyFileSubscriber::init()
{
    // open coms file for reading 
    if (!filename.empty())
    {
        if (oFileReader.open(filename))
            benabled = true;        
    }    
}

std::string AmyFileSubscriber::readInfo()
{
    std::string message = "";

    if (oFileReader.isOpen())        
    {
        // read file from top
        oFileReader.readFromTop();
        // read message in file
        message = oFileReader.readLine();            
    }
    else
    {
        LOG4CXX_ERROR(logger, "AmyFileSubscriber: could not open coms file " << filename);
    }
    
    return message;
}

}
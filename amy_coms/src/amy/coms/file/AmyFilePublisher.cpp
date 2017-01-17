/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/file/AmyFilePublisher.h"
#include "amy/coms/AmyComsConfig.h"

namespace amy
{
log4cxx::LoggerPtr AmyFilePublisher::logger(log4cxx::Logger::getLogger("amy.publisher"));

AmyFilePublisher::AmyFilePublisher()
{    
    // get coms file name
    AmyComsConfig oAmyComsConfig;    
    filename = oAmyComsConfig.getComsFilename2();
}

AmyFilePublisher::~AmyFilePublisher()
{
    oFileWriter.close();    
}

void AmyFilePublisher::init()
{
    // open coms file for writing
    if (!filename.empty())
    {
        if (oFileWriter.open(filename))
            benabled = true;        
    }    
}

void AmyFilePublisher::publishInfo(std::string sollMessage)
{
    if (oFileWriter.isOpen())        
    {
        // overwrite any previous info
        oFileWriter.writeFromTop();
        oFileWriter.writeFlush(sollMessage);
        //LOG4CXX_INFO(logger, "AmyFilePublisher: > " << sollMessage);        
    }
    else
        LOG4CXX_ERROR(logger, "AmyFilePublisher: can't publish info, coms file not open");                
}


}
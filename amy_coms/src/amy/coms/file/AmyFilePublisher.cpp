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
    // open coms file for writing
    if (!filename.empty())
    {
        oFileWriter.open(filename);  
    }
}

AmyFilePublisher::~AmyFilePublisher()
{
    oFileWriter.close();    
}

void AmyFilePublisher::publishInfo()
{
    if (oFileWriter.isOpen())        
    {
        // write command in coms file (newline added)
        std::string message = oArmData.createSollMessage();
        // overwriting any previous command
        oFileWriter.writeFromTop();
        oFileWriter.writeFlush(message);
        //LOG4CXX_INFO(logger, "AmyFilePublisher: command > " << message);        
    }
    else
        LOG4CXX_ERROR(logger, "AmyFilePublisher: can't publish info, coms file not open");                
}


}
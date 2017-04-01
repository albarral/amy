/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/file/AmyFileClient.h"
#include "amy/coms/AmyComsConfig.h"

namespace amy
{
log4cxx::LoggerPtr AmyFileClient::logger(log4cxx::Logger::getLogger("amy.client"));

AmyFileClient::AmyFileClient()
{    
    // get coms file name
    AmyComsConfig oAmyComsConfig;    
    filename = oAmyComsConfig.getComsFilename1();
    // open coms file for writing
    if (!filename.empty())
    {
        oFileWriter.open(filename);  
    }
}

AmyFileClient::~AmyFileClient()
{
    oFileWriter.close();    
}

void AmyFileClient::sendCommand(std::string text)
{
    if (oFileWriter.isOpen())        
    {
        // write command in coms file (newline added)
        std::string output = text + "\n";
        // overwriting any previous command
        oFileWriter.writeFromTop();
        oFileWriter.writeFlush(output);
        LOG4CXX_INFO(logger, "AmyFileClient: command sent");        
    }
    else
        LOG4CXX_ERROR(logger, "AmyFileClient: send failed! coms file not open");                
}

void AmyFileClient::setPort(const int port){
    
}


}
#ifndef __AMY_COMS_FILEPUBLISHER_H
#define __AMY_COMS_FILEPUBLISHER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/coms/AmyPublisher.h"
#include "amy/utils/FileWriter.h"

namespace amy
{
// Implementation of the AmyPublisher class based in broadcasting messages through a shared file.
class AmyFilePublisher : public AmyPublisher
{    
private:
    static log4cxx::LoggerPtr logger;    
    std::string filename;       // file for broadcasting the info
    FileWriter oFileWriter;
    
public:
    AmyFilePublisher();
    ~AmyFilePublisher();

    virtual void init();
    std::string getFilename() {return filename;};
        
private:
   // info publishing method (writes data in file)
    virtual void publishInfo(std::string sollMessage);
};
}
#endif

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
class AmyFilePublisher : public AmyPublisher
{    
private:
    static log4cxx::LoggerPtr logger;    
    std::string filename;
    FileWriter oFileWriter;
    
public:
    AmyFilePublisher();
    ~AmyFilePublisher();

    std::string getFilename() {return filename;};
        
private:
   // info publishing method (writes data in file)
    virtual void publishInfo();
};
}
#endif

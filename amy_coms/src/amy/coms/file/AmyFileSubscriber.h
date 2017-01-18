#ifndef __AMY_COMS_FILESUSBSCRIBER_H
#define __AMY_COMS_FILESUSBSCRIBER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/coms/AmySubscriber.h"
#include "amy/utils/FileReader.h"

namespace amy
{
// Implementation of the AmySubscriber class based in broadcasting messages through a shared file.
class AmyFileSubscriber : public AmySubscriber
{    
private:
    static log4cxx::LoggerPtr logger;
    std::string filename;       // name of file used for coms
    FileReader oFileReader;     // file reader
    
public:
    AmyFileSubscriber();
    ~AmyFileSubscriber();

    virtual void init();
    
    std::string getFilename() {return filename;};

private:
   // info reading method (read data from file)
    virtual std::string readInfo();
    
};
}
#endif

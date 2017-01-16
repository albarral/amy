#ifndef __AMY_CLIENT_FILECLIENT_H
#define __AMY_CLIENT_FILECLIENT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/coms/AmyClient.h"
#include "amy/utils/FileWriter.h"

namespace amy
{
class AmyFileClient : public AmyClient
{    
private:
    static log4cxx::LoggerPtr logger;    
    std::string filename;
    FileWriter oFileWriter;
    
public:
    AmyFileClient();
    ~AmyFileClient();

    std::string getFilename() {return filename;};
        
private:
    // send textual command
    virtual void sendCommand();
};
}
#endif

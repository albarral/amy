#ifndef __AMY_COMS_FILESERVER_H
#define __AMY_COMS_FILESERVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
//#include <log4cxx/logger.h>

#include "amy/coms/AmyServer.h"
#include "amy/utils/FileReader.h"
#include "amy/utils/FileWriter.h"

namespace amy
{
// Implementation of AmyServer base class to allow external control of amy.
// The communication with the client is handled through a shared file.    
class AmyFileServer : public AmyServer
{    
private:
//    static log4cxx::LoggerPtr logger;
    std::string filename;       // name of file used for coms
    FileReader oFileReader;     // file reader
    FileWriter oFileWriter;        // file writer
    std::string text;               // received textual command
    //int result;         // response sent back to client
    
public:
    AmyFileServer();
    ~AmyFileServer();

    std::string getFilename() {return filename;};
    AmyCommand& getAmyCommand() {return oAmyCommand;};
        
    // checks for received requests in the coms file and interprets them
    // returns false if no request received
    bool readCommand();
    // return obtained text
    std::string getText() {return text;};
        
};
}
#endif

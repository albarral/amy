#ifndef __AMY_COMS_FILECLIENT_H
#define __AMY_COMS_FILECLIENT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "amy/coms/AmyClient.h"
#include "amy/utils/FileWriter.h"

namespace amy
{
class AmyFileClient : public AmyClient
{    
private:
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

#ifndef __AMY_SERVER_FILESERVER_H
#define __AMY_SERVER_FILESERVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "amy/coms/AmyCommand.h"
#include "amy/utils/FileReader.h"
#include "amy/core/bus/ArmBus.h"

namespace amy
{
// This module is an amy server. That is, it receives and processes remote control requests for to move an arm or hand.
// The module continuously monitors a text file where clients write their requests.
// The requests are interpreted and converted to control signals that are sent to the amy's bus.
    
class AmyFileServer : public Module2
{    
private:
    bool benabled;
    // bus
    bool bconnected;        // connected to bus
    ArmBus* pArmBus;          // arm bus
    std::string filename;
    AmyCommand oAmyCommand;
    FileReader oFile;
    
public:
    AmyFileServer();

    std::string getFilename() {return filename;};
    AmyCommand& getAmyCommand() {return oAmyCommand;};
    
    // module params
    virtual void init();        
   bool isEnabled() {return benabled;};

   // bus connection 
   void connect(ArmBus* pArmBus);
   bool isConnected() {return bconnected;};
    // ask the module to stop
    void stop();

private:
    void first();
    // executes the behaviour
    void loop ();
    
    void movePan(float value);
    void moveTilt(float value);
    void moveRadius(float value);    
    void endAmy();
};
}
#endif

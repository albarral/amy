#ifndef __AMY_COMS_AMYSERVER_H
#define __AMY_COMS_AMYSERVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/coms/iAmyComs.h"
#include "amy/coms/data/AmyCommand.h"
#include "amy/core/ifaces/iArmInterface.h"

namespace amy
{
// Base class used to serve requests from external processes.
// Implements the iAmyComs interface.
// Requests are transformed into proper calls to amy control interfaces (ie the ArmInterface)
class AmyServer : public iAmyComs
{    
protected:
    static log4cxx::LoggerPtr logger;      
    bool bconnected;        // connected to amy control interfaces
    iArmInterface* pArmInterface;   // interface for arm control
    bool bamyEndRequested;  // flag indicating amy has to end
    AmyCommand oAmyCommand;     // class used to interpret the request      
    bool bvalid;        // indication of valid request
        
public:
    AmyServer();

   bool isConnected() {return bconnected;};
   void connect2Arm(iArmInterface& oArmInterface);
   
   // cyclic movements
    virtual void panFrequency(float value);
    virtual void panAmplitude(float value);
    virtual void panTrigger();
    virtual void panStop();

   // axis speeds        
    virtual void panSpeed(float value);
    virtual void tiltSpeed(float value);
    virtual void radialSpeed(float value);
    virtual void keepTilt(int value);    
   
    // axis positions       
    virtual void movePan(float value);
    virtual void moveTilt(float value);
    virtual void moveRadius(float value);
    
    // joint positions
    virtual void setPosHS(float value);
    virtual void setPosVS(float value);
    virtual void setPosELB(float value);
    virtual void setPosHW(float value);
    virtual void setPosVW(float value);
    
    // arm commands   
    virtual void endAmy();
    
    // dummy method for to do commands
    virtual void toDoCommand(float value);

    bool isAmyEndRequested() {return bamyEndRequested;};
         
    // interprets textual command. returns whether valid or not
    bool checkCommand(std::string text);
   // transforms command into proper call to arm interface
    bool processCommand();
 
private:
    // process command of joint category
    bool processJointCommand();
    // process command of axis category
    bool processAxisCommand();
    // process command of arm category
    bool processArmCommand();
    // process command of amy category
    bool processAmyCommand();

};
}
#endif

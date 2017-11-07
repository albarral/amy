#ifndef __AMY_SHOW_SHOWSENSER_H
#define __AMY_SHOW_SHOWSENSER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/show/ShowData.h"
#include "comy/file/ComyFileSubscriber.h"
#include "talky/talk/Interpreter.h"
#include "tuly/control/module3.h"

namespace amy
{
// Module used to plot an arm's position (for debugging purpose).
// It gets the info from the arm bus.
class ShowSenser : public tuly::Module3
{
private:
    static log4cxx::LoggerPtr logger;      
    bool benabled; 
    ShowData* pShowData;     //  access to shared show data
    comy::ComyFileSubscriber oComySubscriberJoints;     // communications subscriber for joint category
    comy::ComyFileSubscriber oComySubscriberAxis;     // communications subscriber for axis category
    talky::Interpreter oInterpreter;                           // talky language interpreter        

public:
    ShowSenser();
    ~ShowSenser();

    void init(ShowData& oShowData);
    
private:
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();            

    bool processMessage4Joints(std::string rawMessage);    
    bool processMessage4Axes(std::string rawMessage);    
};
}		
#endif

#ifndef __AMY_SHOW_AMYSHOW_H
#define __AMY_SHOW_AMYSHOW_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "comy/file/ComyFileSubscriber.h"
#include "amy/talk/DataBlockAxes.h"
#include "amy/talk/DataBlockJoints.h"
//#include "amy/talk/DataBlockJointDrivers.h"
#include "talky/talk/Interpreter.h"

namespace amy
{
class AmyShow
{
private:    
    static log4cxx::LoggerPtr logger;      
    bool benabled;
    comy::ComyFileSubscriber oComySubscriberJoints;     // communications subscriber for joint category
    comy::ComyFileSubscriber oComySubscriberAxis;     // communications subscriber for axis category
    talky::Interpreter oInterpreter;                           // talky language interpreter        
    DataBlockJoints oDataBlockJoints;                       // data block for joint angles
    //DataBlockJointDrivers oDataBlockJointDrivers;     // data block for joint states
    DataBlockAxes oDataBlockAxes;                        // data block for axes positions and speeds

public:
  AmyShow();
  ~AmyShow();

  bool isEnabled() {return benabled;};

  void senseInfo();
  DataBlockJoints& getDataBlockJoints() {return oDataBlockJoints;};
  //DataBlockJointDrivers& getDataBlockJointDrivers() {return oDataBlockJointDrivers;};
  DataBlockAxes& getDataBlockAxes() {return oDataBlockAxes;};
  
private:
    bool processMessage4Joints(std::string rawMessage);    
    bool processMessage4Axes(std::string rawMessage);    
};
}		

#endif

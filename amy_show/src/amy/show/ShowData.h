#ifndef __AMY_SHOW_SHOWDATA_H
#define __AMY_SHOW_SHOWDATA_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>

#include "amy/talk/DataBlockAxes.h"
#include "amy/talk/DataBlockJoints.h"
//#include "amy/talk/DataBlockJointDrivers.h"

namespace amy
{
class ShowData
{
private:    
    std::mutex mutex;
    DataBlockJoints oDataBlockJoints;                       // data block for joint angles
    //DataBlockJointDrivers oDataBlockJointDrivers;     // data block for joint states
    DataBlockAxes oDataBlockAxes;                        // data block for axes positions and speeds

public:
  ShowData();
  ~ShowData();

  DataBlockJoints& getDataBlockJoints() {return oDataBlockJoints;};
  //DataBlockJointDrivers& getDataBlockJointDrivers() {return oDataBlockJointDrivers;};
  DataBlockAxes& getDataBlockAxes() {return oDataBlockAxes;};
};
}		

#endif

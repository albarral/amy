#ifndef __AMY_SHOW_SHOWSENSER_H
#define __AMY_SHOW_SHOWSENSER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/show/ShowData.h"
#include "amy/core/bus/ArmBus.h"
#include "amy/core/bus/AxisBus.h"
#include "amy/core/bus/JointBus.h"
#include "tuly/control/module3.h"

namespace amy
{
// Module used to plot an arm's position (for debugging purpose).
// It gets the info from the arm bus.
class ShowSenser : public tuly::Module3
{
private:
    static log4cxx::LoggerPtr logger;      
     // bus
    bool bconnected;        // connected to bus
    JointBus* pHSBus;     // access to arm's HS joint
    JointBus* pVSBus;     // access to arm's VS joint
    JointBus* pELBus;     // access to arm's ELB joint
    AxisBus* pPanBus;      // access to pan bus 
    AxisBus* pTiltBus;      // access to tilt bus
    AxisBus* pRadialBus;      // access to radial bus
    // logic
    bool benabled; 
    ShowData* pShowData;     //  access to shared show data

public:
    ShowSenser();
    ~ShowSenser();
        
    // bus connection 
    void connect(ArmBus& oArmBus);
    bool isConnected() {return bconnected;};
    void init(ShowData& oShowData);
    
private:
    // first actions when the thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();            
};
}		
#endif

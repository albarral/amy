/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/AmyShow.h"

namespace amy
{
log4cxx::LoggerPtr AmyShow::logger(log4cxx::Logger::getLogger("amy.show"));

AmyShow::AmyShow() 
{
}

AmyShow::~AmyShow()
{    
}
     
 bool AmyShow::launch(ArmBus& oArmBus)
{
    LOG4CXX_INFO(logger, "AmyShow: launch modules");
    float freq = 10.0;
     
    // launch senser module
    oShowSenser.connect(oArmBus);
    oShowSenser.init(oShowData);
    oShowSenser.setFrequency(freq);
    oShowSenser.on();

    // launch plotter module
    oShowPlotter.init(oShowData);
    oShowPlotter.setFrequency(freq);
    oShowPlotter.on();      
    
    return true;
  }

bool AmyShow::end()
{
    LOG4CXX_INFO(logger, "AmyShow: end modules");
    // finish senser module
    oShowSenser.off();
    oShowSenser.wait();      

    // finish plotter module
    oShowPlotter.off();
    oShowPlotter.wait();      
    
    return true;
}

}		

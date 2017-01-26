#ifndef AMYZEROMQPUBLISHER_H
#define AMYZEROMQPUBLISHER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   oriol.orra@migtron.com   *
 ***************************************************************************/

#include <string>
#include <iostream>
#include <log4cxx/logger.h>
#include <zmq.hpp>

#include "amy/coms/AmyPublisher.h"

namespace amy
{
// Implementation of the AmyPublisher class based in broadcasting messages through a shared file.
class AmyZeroMQPublisher : public AmyPublisher
{    
private:
    static log4cxx::LoggerPtr logger;
    std::string publisherPort;
    
public:
    
    AmyZeroMQPublisher();
    ~AmyZeroMQPublisher();

    void setPort(const int port);
    virtual void init();
        
private:
   // info publishing method (writes data in file)
    virtual void publishInfo(std::string sollMessage);
};
}

#endif /* AMYZEROMQPUBLISHER_H */


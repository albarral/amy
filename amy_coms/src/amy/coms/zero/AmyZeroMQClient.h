#ifndef AMYZEROMQ_H
#define AMYZEROMQ_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   oriol.orra@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>
#include <iostream>
#include <string>
#include <zmq.hpp>

#include "amy/coms/AmyClient.h"

namespace amy
{
    class AmyZeroMQClient : public AmyClient
    {       
        private:
            static log4cxx::LoggerPtr logger;
            std::string clientPort;
        public:
            AmyZeroMQClient();    
            ~AmyZeroMQClient();
            
            void setPort(const int port);

        private:
            // send textual command
            virtual void sendCommand();
    };
}

#endif


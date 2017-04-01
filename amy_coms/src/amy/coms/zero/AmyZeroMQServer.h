#ifndef AMYZEROMQSERVER_H
#define AMYZEROMQSERVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   oriol@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>
#include <string>
#include <iostream>

#include "amy/coms/AmyServer.h"
#include <zmq.hpp>

struct Responses{
    const std::string valid = "OK";
    const std::string invalid = "NO";
};

namespace amy
{
    // Implementation of AmyServer base class to allow external control of amy.
    // The communication with the client is handled through a shared file.    
    class AmyZeroMQServer : public AmyServer
    {    
        private:
            static log4cxx::LoggerPtr logger;
            AmyCommand oAmyCommand;     // class used to interpret the request
            bool bvalid;        // indication of valid request
            std::string portString;
            std::string text;               // received textual command
        public:

            Responses response;    

            AmyZeroMQServer();
            ~AmyZeroMQServer();

            void setPort(const int port);
            AmyCommand& getAmyCommand() {return oAmyCommand;};

            // checks for received requests in the coms file and interprets them
            // returns false if no request received
            bool readCommand();
            
            // returns whether command is valid or not
            bool isValid() {return bvalid;};
            
            std::string getText() {return text;};
    };
}

#endif /* AMYZEROMQSERVER_H */


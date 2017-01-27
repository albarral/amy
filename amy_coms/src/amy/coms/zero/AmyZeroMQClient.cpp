/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   oriol.orra@migtron.com   *
 ***************************************************************************/

#include "amy/coms/zero/AmyZeroMQClient.h"
#include "amy/coms/AmyComsConfig.h"

namespace amy
{
    log4cxx::LoggerPtr AmyZeroMQClient::logger(log4cxx::Logger::getLogger("amy.client"));

    //  Prepare our context and socket
    zmq::context_t contextClient (1);
    zmq::socket_t socketClient (contextClient, ZMQ_REQ);
    
    AmyZeroMQClient::AmyZeroMQClient()
    {        
        
    }

    AmyZeroMQClient::~AmyZeroMQClient()
    {
        socketClient.close();
        LOG4CXX_INFO(logger, "Client ZMQ closing...");
    }
    
    void AmyZeroMQClient::setPort(const int port){
        clientPort = std::to_string(port);
        socketClient.connect ("tcp://localhost:"+clientPort);
        LOG4CXX_INFO(logger, "Client ZMQ connecting...");
    }

    void AmyZeroMQClient::sendCommand()
    {
        std::string command = oAmyCommand.getText();
        
        //Send Command
        zmq::message_t request (command.length());
        memcpy (request.data (), command.c_str(), command.length());
        std::cout << "Sending request... " << command << std::endl;
        socketClient.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socketClient.recv (&reply);
        std::string rpl = std::string(static_cast<char*>(reply.data()), reply.size());
        std::cout << "Received-> " << rpl << std::endl;
    }
}
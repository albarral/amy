/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   oriol@migtron.com   *
 ***************************************************************************/

#include "AmyZeroMQServer.h"

namespace amy
{
    log4cxx::LoggerPtr AmyZeroMQServer::logger(log4cxx::Logger::getLogger("amy.server"));

    zmq::context_t contextServer (1); //creates the context 
    zmq::socket_t socketServer (contextServer, ZMQ_REP); //creates the socket
    
    AmyZeroMQServer::AmyZeroMQServer()
    {    
        //socketServer.setsockopt(ZMQ_RCVTIMEO, 500);
        //socketServer.setsockopt(ZMQ_SNDTIMEO,500);
    }

    AmyZeroMQServer::~AmyZeroMQServer()
    {
        socketServer.close();
        LOG4CXX_INFO(logger, "Server ZMQ closing...");
    }

    void AmyZeroMQServer::setPort(const int port){

        portString = std::to_string(port);
        socketServer.bind("tcp://*:"+portString); //and binds it

        LOG4CXX_INFO(logger, "Server ZMQ connecting 2 sockets..." +port);
    }

    bool AmyZeroMQServer::readCommand()
    {
        bool brequest = false;  // default no request received
        try{
            zmq::message_t request;

            //  Wait for next request from client
            brequest = socketServer.recv (&request);
            text = std::string(static_cast<char*>(request.data()), request.size());
            std::cout << "Received-> " << text << std::endl;

            //Send reply
            std::string buffer="OK";
            zmq::message_t reply (buffer.length());
            memcpy (reply.data (), buffer.c_str(), buffer.length());
            std::cout << "Sending reply..." << std::endl;
            socketServer.send (reply);

            return brequest;
        }catch(zmq::error_t& e) {
                std::cout << "ERROR: Client -> Sending before receiving a request." << std::endl;
        }
    }
}

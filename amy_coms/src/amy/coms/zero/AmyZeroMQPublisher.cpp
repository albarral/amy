/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   oriol.orra@migtron.com   *
 ***************************************************************************/

#include "amy/coms/zero/AmyZeroMQPublisher.h"

namespace amy
{
log4cxx::LoggerPtr AmyZeroMQPublisher::logger(log4cxx::Logger::getLogger("amy.publisher"));

zmq::context_t contextPublisher (1); //creates the context 
zmq::socket_t socketPublisher (contextPublisher, ZMQ_REP); //creates the socket

AmyZeroMQPublisher::AmyZeroMQPublisher()
{    
    //socketPublisher.setsockopt(ZMQ_RCVTIMEO, 500);
    //socketPublisher.setsockopt(ZMQ_SNDTIMEO,500);
}

AmyZeroMQPublisher::~AmyZeroMQPublisher()
{
    socketPublisher.close();
    LOG4CXX_INFO(logger, "Publisher ZMQ closing... ");
}

void AmyZeroMQPublisher::setPort(const int port){
    publisherPort = std::to_string(port);
    socketPublisher.bind ("tcp://*:"+publisherPort); //and binds it
    LOG4CXX_INFO(logger, "Publisher ZMQ connecting...");
}

void AmyZeroMQPublisher::init()
{
    if(socketPublisher.connected())
        benabled = true;        
    else
        LOG4CXX_ERROR(logger, "AmyZeroMQPublisher: cannot connect"); 
}

void AmyZeroMQPublisher::publishInfo(std::string sollMessage)
{
    try{
        //  Get the reply.
        zmq::message_t request;
        socketPublisher.recv (&request);
        std::string requestString = std::string(static_cast<char*>(request.data()), request.size());
        std::cout << "Received-> " << requestString << std::endl;
        
        //Send Command
        zmq::message_t armMessage (sollMessage.length());
        memcpy (armMessage.data (), sollMessage.c_str(), sollMessage.length());
        std::cout << "Sending Arm message..." << std::endl;
        socketPublisher.send(armMessage);


    }catch(zmq::error_t& e) {
            std::cout << "ERROR: Publisher -> Sending before receiving a request." << std::endl;
    }
}

}

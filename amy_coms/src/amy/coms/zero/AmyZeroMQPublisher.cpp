/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   oriol.orra@migtron.com   *
 ***************************************************************************/

#include "amy/coms/zero/AmyZeroMQPublisher.h"

namespace amy
{
log4cxx::LoggerPtr AmyZeroMQPublisher::logger(log4cxx::Logger::getLogger("amy.publisher"));

zmq::context_t contextPublisher (1); //creates the context 
zmq::socket_t socketPublisher (contextPublisher, ZMQ_REQ); //creates the socket

AmyZeroMQPublisher::AmyZeroMQPublisher()
{    
   
}

AmyZeroMQPublisher::~AmyZeroMQPublisher()
{
    
}

void AmyZeroMQPublisher::init()
{
    if(socketPublisher.connected())
        benabled = true;        
    
}

void AmyZeroMQPublisher::setPort(const int port){
    publisherPort = std::to_string(port);
    socketPublisher.bind ("tcp://*:"+publisherPort); //and binds it
    std::cout << "Publisher connecting..." << std::endl;
}

void AmyZeroMQPublisher::publishInfo(std::string sollMessage)
{
    //Send Command
    zmq::message_t armMessage (sollMessage.length());
    memcpy (armMessage.data (), sollMessage.c_str(), sollMessage.length());
    std::cout << "Sending Arm message..." << std::endl;
    socketPublisher.send(armMessage);
    
    //  Get the reply.
    zmq::message_t reply;
    socketPublisher.recv (&reply);
    std::string rpl = std::string(static_cast<char*>(reply.data()), reply.size());
    std::cout << "Received-> " << rpl << std::endl;
}

}

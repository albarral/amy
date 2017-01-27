/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/coms/zero/AmyZeroMQSubscriber.h"
#include "amy/coms/AmyComsConfig.h"

namespace amy
{
log4cxx::LoggerPtr AmyZeroMQSubscriber::logger(log4cxx::Logger::getLogger("amy.subscriber"));

zmq::context_t contextSubscriber (1); //creates the context 
zmq::socket_t socketSubscriber (contextSubscriber, ZMQ_REP); //creates the socket


AmyZeroMQSubscriber::AmyZeroMQSubscriber()
{
    
}

AmyZeroMQSubscriber::~AmyZeroMQSubscriber()
{
    socketSubscriber.close();
    LOG4CXX_INFO(logger, "Subscriber ZMQ closing... ");
}

void AmyZeroMQSubscriber::setPort(const int port){
    subscriberPort = std::to_string(port);
    socketSubscriber.bind ("tcp://*:"+subscriberPort); //and binds it
    std::cout << "Subscriber connecting..." << std::endl;
    LOG4CXX_INFO(logger, "Subscriber ZMQ connecting... ");
}

void AmyZeroMQSubscriber::init()
{
    // open coms for reading 
    if(socketSubscriber.connected())
        benabled = true;  
    else
        LOG4CXX_ERROR(logger, "AmyZeroMQSubscriber: cannot connect"); 
}

std::string AmyZeroMQSubscriber::readInfo()
{   
    zmq::message_t msg;
    
    //  Wait for next request from Publisher
    socketSubscriber.recv (&msg);
    std::string message = std::string(static_cast<char*>(msg.data()), msg.size());
    std::cout << "Received-> "<< message << std::endl;
    
    //Send reply
    std::string response = "OK";
            
    zmq::message_t reply (response.length());
    memcpy (reply.data (), response.c_str(), response.length());
    std::cout << "Sending reply..." << std::endl;
    socketSubscriber.send (reply);
    
    return message;
}

}

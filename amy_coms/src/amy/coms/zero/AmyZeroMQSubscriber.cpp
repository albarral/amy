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
zmq::socket_t socketSubscriber (contextSubscriber, ZMQ_REQ); //creates the socket


AmyZeroMQSubscriber::AmyZeroMQSubscriber()
{
    //socketSubscriber.setsockopt(ZMQ_RCVTIMEO, 500);
    socketSubscriber.setsockopt(ZMQ_SNDTIMEO,500);
    socketSubscriber.setsockopt(ZMQ_REQ_CORRELATE,1);
    socketSubscriber.setsockopt(ZMQ_REQ_RELAXED,1);
}

AmyZeroMQSubscriber::~AmyZeroMQSubscriber()
{
    socketSubscriber.close();
    LOG4CXX_INFO(logger, "Subscriber ZMQ closing... ");
}

void AmyZeroMQSubscriber::setPort(const int port){
    subscriberPort = std::to_string(port);
    socketSubscriber.connect("tcp://localhost:"+subscriberPort); //and binds it
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
    try{
        
        //Send request
        std::string response = "OK";

        zmq::message_t request (response.length());
        memcpy (request.data (), response.c_str(), response.length());
        std::cout << "Sending reply..." << std::endl;
        socketSubscriber.send (request);
        
        zmq::message_t msg;
        //  Wait for next request from Publisher
        socketSubscriber.recv (&msg);
        std::string message = std::string(static_cast<char*>(msg.data()), msg.size());
        std::cout << "Received-> 1"<< message << std::endl;

        return message;

    }catch(zmq::error_t& e) {
        std::cout << e.what() << std::endl;
    }
}

}

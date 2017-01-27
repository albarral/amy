/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AmyZeroMQSubscriber.h
 * Author: oriol
 *
 * Created on January 27, 2017, 5:56 PM
 */

#ifndef AMYZEROMQSUBSCRIBER_H
#define AMYZEROMQSUBSCRIBER_H


/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   oriol.orra@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>
#include <zmq.hpp>
#include <string>
#include <iostream>
#include "amy/coms/AmySubscriber.h"

namespace amy
{
// Implementation of the AmySubscriber class based in broadcasting messages through a shared file.
class AmyZeroMQSubscriber : public AmySubscriber
{    
private:
    static log4cxx::LoggerPtr logger;
    std::string subscriberPort;
    
public:
    AmyZeroMQSubscriber();
    ~AmyZeroMQSubscriber();

    void setPort(const int port);
    virtual void init();
    

private:
   // info reading method (read data from file)
    virtual std::string readInfo();
    
};
}

#endif /* AMYZEROMQSUBSCRIBER_H */


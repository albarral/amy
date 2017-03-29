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
zmq::socket_t socketControlGui (contextServer, ZMQ_REP); //creates the socket

AmyZeroMQServer::AmyZeroMQServer()
{    
    //socketServer.setsockopt(ZMQ_RCVTIMEO, 500);
    //socketServer.setsockopt(ZMQ_SNDTIMEO,500);
}

AmyZeroMQServer::~AmyZeroMQServer()
{
    socketServer.close();
    socketControlGui.close();
    LOG4CXX_INFO(logger, "Server ZMQ closing...");
}

void AmyZeroMQServer::setPort(const int portTesting, const int portControlGui){
    portTestingString = std::to_string(portTesting);
    portControlGuiString = std::to_string(portControlGui);
    
    socketServer.bind("tcp://*:"+portTestingString); //and binds it
    socketControlGui.bind("tcp://*:"+portControlGuiString); //and binds it
    
    LOG4CXX_INFO(logger, "Server ZMQ connecting 2 sockets..." +portTestingString+"   "+portControlGuiString);
}

bool AmyZeroMQServer::readCommandTesting()
{
    bool brequest = false;  // default no request received
    try{
        zmq::message_t request;

        //  Wait for next request from client
        brequest = socketServer.recv (&request);
        std::string stringRequest = std::string(static_cast<char*>(request.data()), request.size());
        std::cout << "Received-> "<< stringRequest << std::endl;
        bvalid = oAmyCommand.interpret(stringRequest);

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

bool AmyZeroMQServer::readCommandControl()
{
    bool brequest = false;  // default no request received
    std::cout << "Read Control" << std::endl;
    try{
        zmq::message_t request;

        //  Wait for next request from client
        brequest = socketControlGui.recv (&request);
        std::string stringRequest = std::string(static_cast<char*>(request.data()), request.size());
        std::cout << "Received Control -> "<< stringRequest << std::endl;
        //bvalid = oAmyCommand.interpret(stringRequest);

        //Send reply
        std::string buffer="OK";

        zmq::message_t reply (buffer.length());
        memcpy (reply.data (), buffer.c_str(), buffer.length());
        std::cout << "Sending reply..." << std::endl;
        socketControlGui.send(reply);

        return brequest;
    }catch(zmq::error_t& e) {
            std::cout << "ERROR: Client -> Sending before receiving a request." << std::endl;
    }
}

void AmyZeroMQServer::processCommand()
{
    switch (oAmyCommand.getAction())
    {
        case AmyCommand::eACT_MOVE_ARM:
            processArmCommand();
            break;
            
        case AmyCommand::eACT_MOVE_JOINT:
            processJointCommand();
            break;

        case AmyCommand::eACT_END_AMY:
            LOG4CXX_INFO(logger, "> end amy");                        
            endAmy();
            break;

        default:
            LOG4CXX_WARN(logger, "AmyFileServer: unknown action");                        
    }    
}

void AmyZeroMQServer::processArmCommand()
{
    float value = oAmyCommand.getValue();

    switch (oAmyCommand.getTarget())
    {
        case AmyCommand::eTAR_PAN:
            LOG4CXX_INFO(logger, "> move pan " << value);                        
            AmyServer::movePan(value);
            break;
            
        case AmyCommand::eTAR_TILT:
            LOG4CXX_INFO(logger, "> move tilt " << value);                        
            AmyServer::moveTilt(value);
            break;

        case AmyCommand::eTAR_RADIUS:
            LOG4CXX_INFO(logger, "> move radius " << value);                        
            AmyServer::moveRadius(value);
            break;

        default:
            LOG4CXX_WARN(logger, "AmyFileServer: unknown arm target");                        
    }    
}

void AmyZeroMQServer::processJointCommand()
{
    float value = oAmyCommand.getValue();

    switch (oAmyCommand.getTarget())
    {
        case AmyCommand::eTAR_JOINT_HSHOULDER:
            LOG4CXX_INFO(logger, "> set HS " << value);                        
            AmyServer::setPosHS(value);
            break;
            
        case AmyCommand::eTAR_JOINT_VSHOULDER:
            LOG4CXX_INFO(logger, "> set VS " << value);                        
            AmyServer::setPosVS(value);
            break;

        case AmyCommand::eTAR_JOINT_ELBOW:
            LOG4CXX_INFO(logger, "> set ELB " << value);                        
            AmyServer::setPosELB(value);
            break;

        case AmyCommand::eTAR_JOINT_HWRIST:
            LOG4CXX_INFO(logger, "> set HW " << value);                        
            AmyServer::setPosHW(value);
            break;

        case AmyCommand::eTAR_JOINT_VWRIST:
            LOG4CXX_INFO(logger, "> set VW " << value);                        
            AmyServer::setPosVW(value);
            break;

        default:
            LOG4CXX_WARN(logger, "AmyFileServer: unknown joint target");                        
    }    
}

}
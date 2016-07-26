/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/network/ArmNetwork.h"
#include "amy/network/config/NetworkConfig.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmNetwork::logger(Logger::getLogger("amy.network"));

// Constructor
ArmNetwork::ArmNetwork ()
{    
    benabled = false;
    NetworkConfig oNetworkConfig;
    pDBClient = new DBClient(oNetworkConfig.getDBServerUrl(), oNetworkConfig.getDBName(), oNetworkConfig.getDBUser(), oNetworkConfig.getDBPassword());
    tabJoints = oNetworkConfig.getTabArmJoints();
}

// Destructor
ArmNetwork::~ArmNetwork ()
{
    if (pDBClient != 0)
    delete (pDBClient);
}

// sets soll (commanded) values for all joints
void ArmNetwork::setSollJoints(float value1, float value2, float value3, float value4, float value5)
{
    soll1 = value1;
    soll2 = value2;
    soll3 = value3;
    soll4 = value4;
    soll5 = value5;
    
    writeDBSoll();
}

// gets soll (commanded) values for all joints
void ArmNetwork::getSollJoints(float& value1, float& value2, float& value3, float& value4, float& value5)
{
    readDBSoll();
    
    value1 = soll1;
    value2 = soll2;
    value3 = soll3;
    value4 = soll4;
    value5 = soll5;
}

// sets ist (measured) values for all joints
void ArmNetwork::setIstJoints(float value1, float value2, float value3, float value4, float value5)
{
    ist1 = value1;
    ist2 = value2;
    ist3 = value3;
    ist4 = value4;
    ist5 = value5;
    
    writeDBIst();
}

// gets ist (measured) values for all joints
void ArmNetwork::getIstJoints(float& value1, float& value2, float& value3, float& value4, float& value5)
{
    readDBIst();

    value1 = ist1;
    value2 = ist2;
    value3 = ist3;
    value4 = ist4;
    value5 = ist5;
}

bool ArmNetwork::connectDB()
{
    pDBClient->connect();    
    // true if connection ok
    return (pDBClient->isConnected());    
}

bool ArmNetwork::writeDBSoll()
{        
    LOG4CXX_INFO(logger, "ArmNetwork: write DB soll");
    
    // try reconnection
    if (!connectDB())
    {
        LOG4CXX_ERROR(logger, "ArmNetwork: failed DB connection!");
        return false;
    }

    // update all joint values
    std::string query = "UPDATE " +  tabJoints + " SET " + 
                                + "joint1 = " + std::to_string(soll1) +  
                                + ", joint2 = " + std::to_string(soll2) +  
                                + ", joint3 = " + std::to_string(soll3) +  
                                + ", joint4 = " + std::to_string(soll4) +  
                                + ", joint5 = " + std::to_string(soll5);
    
    pDBClient->write(query);
    pDBClient->commit();   
    return true;
}


bool  ArmNetwork::readDBSoll()
{        
    LOG4CXX_INFO(logger, "ArmNetwork: read DB soll");
    
    // try reconnection
    if (!connectDB())
    {
        LOG4CXX_ERROR(logger, "ArmNetwork: failed DB connection!");
        return false;
    }
        
    std::string query = "SELECT * FROM " + tabJoints;
    sql::ResultSet* res = pDBClient->read(query);
      
    if (res->next())
    {
        soll1 = (float)res->getDouble("joint1");
        soll2 = (float)res->getDouble("joint2");
        soll3 = (float)res->getDouble("joint3");
        soll4 = (float)res->getDouble("joint4");
        soll5 = (float)res->getDouble("joint5");
    }
    return true;
}

}

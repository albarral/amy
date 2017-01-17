/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "amy/network/DBArmStorage.h"
#include "amy/network/config/NetworkConfig.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr DBArmStorage::logger(Logger::getLogger("amy.network"));

// Constructor
DBArmStorage::DBArmStorage ()
{    
    NetworkConfig oNetworkConfig;
    pDBClient = new DBClient(oNetworkConfig.getDBServerUrl(), oNetworkConfig.getDBName(), oNetworkConfig.getDBUser(), oNetworkConfig.getDBPassword());
    tabJoints = oNetworkConfig.getTabArmJoints();
}

// Destructor
DBArmStorage::~DBArmStorage ()
{
    if (pDBClient != 0)
    delete (pDBClient);
}


// sets soll (commanded) values for all joints
bool DBArmStorage::storeArmSoll(int arm, ArmDataN& oArmData)
{
    LOG4CXX_DEBUG(logger, "DBArmStorage: store arm soll");
    
    // try reconnection
    if (!connectDB())
        return false;

    // update soll joint values
    std::string query = updateQuery4Soll(arm, oArmData);    

    try 
    {
        pDBClient->write(query);
        //pDBClient->commit();   // not necessary, autocommit is set
        return true;
    }
    catch (const sql::SQLException& ex)
    {
      LOG4CXX_ERROR(logger, "DBArmStorage.storeArmSoll failed! " << ex.what());
      return false;        
    }
}


// sets ist (measured) values for all joints
bool DBArmStorage::storeArmIst(int arm, ArmDataN& oArmData)
{
    LOG4CXX_DEBUG(logger, "DBArmStorage: store arm ist");
    
    // try reconnection
    if (!connectDB())
        return false;

    // update ist joint values
    std::string query = updateQuery4Ist(arm, oArmData);    

    try 
    {
        pDBClient->write(query);
        //pDBClient->commit();   // not necessary, autocommit is set
        return true;
    }
    catch (const sql::SQLException& ex)
    {
      LOG4CXX_ERROR(logger, "DBArmStorage.storeArmIst failed! " << ex.what());
      return false;        
    }
}


// gets soll (commanded) values for all joints
bool DBArmStorage::readArmSoll(int arm, ArmDataN& oArmData)
{
    bool bread = false;
    LOG4CXX_DEBUG(logger, "DBArmStorage: read arm soll");
    
    // try reconnection
    if (!connectDB())
        return false;
        
    // read soll joint values
    std::string query = selectQuery4Soll(arm);

    try 
    {
        sql::ResultSet* res = pDBClient->read(query);
        // if data read, return it in ArmData object
        if (res->next())
        {
            oArmData.setSoll1((float)res->getDouble("joint1"));
            oArmData.setSoll2((float)res->getDouble("joint2"));
            oArmData.setSoll3((float)res->getDouble("joint3"));
            oArmData.setSoll4((float)res->getDouble("joint4"));
            oArmData.setSoll5((float)res->getDouble("joint5"));
            bread = true;
        }
    }
    catch (const sql::SQLException& ex)
    {
      LOG4CXX_ERROR(logger, "DBArmStorage.readArmSoll failed! " << ex.what());
    }
    
    return bread;
}


// gets ist (measured) values for all joints
bool DBArmStorage::readArmIst(int arm, ArmDataN& oArmData)
{
    LOG4CXX_DEBUG(logger, "DBArmStorage: read arm ist");
    
    // try reconnection
    if (!connectDB())
        return false;
        
    // read ist joint values
    std::string query = selectQuery4Ist(arm);

    try 
    {
        sql::ResultSet* res = pDBClient->read(query);
        // if data read, return it in ArmData object
        if (res->next())
        {
            oArmData.setIst1((float)res->getDouble("joint1"));
            oArmData.setIst2((float)res->getDouble("joint2"));
            oArmData.setIst3((float)res->getDouble("joint3"));
            oArmData.setIst4((float)res->getDouble("joint4"));
            oArmData.setIst5((float)res->getDouble("joint5"));
        }
        return true;
    }
    catch (const sql::SQLException& ex)
    {
      LOG4CXX_ERROR(logger, "DBArmStorage.readArmIst failed! " << ex.what());
      return false;        
    }
}


bool DBArmStorage::connectDB()
{
    try
    {
        pDBClient->connect();    
        // true if connection ok
        return (pDBClient->isConnected());    
    }
    catch (const sql::SQLException& ex)
    {        
      LOG4CXX_ERROR(logger, "DBArmStorage: failed DB connection!" << ex.what());
      return false;
    }    
}


 std::string DBArmStorage::updateQuery4Soll(int arm, ArmDataN& oArmData)
{
    // update soll values
    std::string query = "UPDATE " +  tabJoints + " SET " + 
                                + "joint1 = " + std::to_string(oArmData.getSoll1()) +  
                                + ", joint2 = " + std::to_string(oArmData.getSoll2()) +  
                                + ", joint3 = " + std::to_string(oArmData.getSoll3()) +  
                                + ", joint4 = " + std::to_string(oArmData.getSoll4()) +  
                                + ", joint5 = " + std::to_string(oArmData.getSoll5()) +
                                " where arm = " + std::to_string(arm) + 
                                " and info = " + std::to_string(eINFO_SOLL);
    
    return query;
}


 std::string DBArmStorage::updateQuery4Ist(int arm, ArmDataN& oArmData)
{
    // update ist values
    std::string query = "UPDATE " +  tabJoints + " SET " + 
                                + "joint1 = " + std::to_string(oArmData.getIst1()) +  
                                + ", joint2 = " + std::to_string(oArmData.getIst2()) +  
                                + ", joint3 = " + std::to_string(oArmData.getIst3()) +  
                                + ", joint4 = " + std::to_string(oArmData.getIst4()) +  
                                + ", joint5 = " + std::to_string(oArmData.getIst5()) +
                                " where arm = " + std::to_string(arm) +
                                " and info = " + std::to_string(eINFO_IST);

    return query;
}

 
std::string DBArmStorage::selectQuery4Soll(int arm)
{
     // select soll values         
     std::string query = "SELECT * FROM " + tabJoints + 
                                " where arm = " + std::to_string(arm) + 
                                " and info = " + std::to_string(eINFO_SOLL);

    return query;
}

std::string DBArmStorage::selectQuery4Ist(int arm)
{
     // select ist values         
     std::string query = "SELECT * FROM " + tabJoints + 
                                " where arm = " + std::to_string(arm) + 
                                " and info = " + std::to_string(eINFO_IST);

    return query;
}
  
}

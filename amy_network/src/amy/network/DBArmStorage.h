#ifndef __AMY_DBARM_STORAGE_H
#define __AMY_DBARM_STORAGE_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/network/iArmStorage.h"
#include "amy/network/db/DBClient.h"

namespace amy
{
// Implementation of the ArmStorage interface where the arm's data is stored in a DB (mysql)
class DBArmStorage : public iArmStorage
{
private:
        // types of info stored in TAB_JOINTS
        enum eInfo
        {
            eINFO_SOLL,  /*! soll (commanded) values */
            eINFO_IST      /*! ist (measured) values */        
        };
    
        static log4cxx::LoggerPtr logger;
        DBClient* pDBClient;
        std::string tabJoints;  // name of joints DB table

public:
        DBArmStorage();
        ~DBArmStorage();
    
        // sets soll (commanded) values for all joints
        virtual bool storeArmSoll(int arm, ArmData& oArmData);
        // sets ist (measured) values for all joints
        virtual bool storeArmIst(int arm, ArmData& oArmData);
        // gets soll (commanded) values for all joints
        virtual bool readArmSoll(int arm, ArmData& oArmData);        
        // gets ist (measured) values for all joints
        virtual bool readArmIst(int arm, ArmData& oArmData);      
        
private:
    // connects to DB
    bool connectDB();    
    // creates the update query to change the joints soll values
    std::string updateQuery4Soll(int arm, ArmData& oArmData);
    // creates the select query to read the joints soll values
    std::string selectQuery4Soll(int arm);
    // creates the update query to change the joints ist values
    std::string updateQuery4Ist(int arm, ArmData& oArmData);
    // creates the select query to read the joints ist values
    std::string selectQuery4Ist(int arm);
    
};

}    
#endif

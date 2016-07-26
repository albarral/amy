#ifndef __AMY_ARM_NETWORK_H
#define __AMY_ARM_NETWORK_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "amy/network/db/DBClient.h"

namespace amy
{
// This class manages the amy's network for arm control
class ArmNetwork
{
    private:
        static log4cxx::LoggerPtr logger;
        bool benabled;
        // (commanded) soll angles of joints 1 to 5
        float soll1;    
        float soll2;    
        float soll3;    
        float soll4;    
        float soll5;    
        // (measured) ist angles of joints 1 to 5
        float ist1;     
        float ist2;      
        float ist3;     
        float ist4;     
        float ist5;     
        DBClient* pDBClient;
        std::string tabJoints;  // name of joints DB table

    public:
        ArmNetwork();
        ~ArmNetwork();

        // inits arm network (DB connection ...)
        void init();
        
        // sets soll (commanded) values for all joints
        void setSollJoints(float value1, float value2, float value3, float value4, float value5);
        // gets soll (commanded) values for all joints
        void getSollJoints(float& value1, float& value2, float& value3, float& value4, float& value5);        
        // sets ist (measured) values for all joints
        void setIstJoints(float value1, float value2, float value3, float value4, float value5);
        // gets ist (measured) values for all joints
        void getIstJoints(float& value1, float& value2, float& value3, float& value4, float& value5);      
        
private:
    // connects to DB
    bool connectDB();
    // store joint soll values in DB
    bool writeDBSoll();
    // read joint soll values from DB
    bool readDBSoll();
    // store joints ist values in DB
    bool writeDBIst();
    // read joint ist values from DB
    bool readDBIst();
    
};

}    
#endif

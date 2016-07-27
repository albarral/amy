/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/network/config/NetworkConfig.h"

namespace amy 
{
// Constructor
NetworkConfig::NetworkConfig ()
{               
    dbServerUrl = "tcp://127.0.0.1:3306"; // mysql server
    dbUser = "amy";
    dbPassword = "amypwd";
    dbName = "DB_AMY";
   
    tabArmJoints = "TAB_JOINTS";
}

}

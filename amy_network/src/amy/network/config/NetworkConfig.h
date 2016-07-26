#ifndef __AMY_NETWORK_CONFIG_H
#define __AMY_NETWORK_CONFIG_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy 
{
// Class for reading the configuration of the Backbone system (to do ... from a file)    
class NetworkConfig 
{
    private:                
        // params for connecting to the backbone database
        std::string dbServerUrl;
        std::string dbUser;
        std::string dbPassword;
        std::string dbName;

        // arm tables
        std::string tabArmJoints;
        
    public:
        NetworkConfig();

        std::string getDBServerUrl() {return this->dbServerUrl;};
        std::string getDBUser() {return this->dbUser;};
        std::string getDBPassword() {return this->dbPassword;};
        std::string getDBName() {return this->dbName;};

        std::string getTabArmJoints() {return tabArmJoints;};
};

}

#endif

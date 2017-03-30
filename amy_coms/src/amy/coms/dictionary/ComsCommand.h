#ifndef __AMY_COMS_COMSCOMMAND_H
#define __AMY_COMS_COMSCOMMAND_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
// Class used to represent communication commands.
 class ComsCommand
{
protected:    
    int category;          /*! category to which the command belongs */
    int ID;                    /*! command ID */
    std::string name;   /*! command name */    
    int numElements;   /*! additional elements needed to complete the command */
    std::string description;   /*! command description */    
    
public:
    ComsCommand();        
    ComsCommand(int category, int ID, std::string name, int numElements, std::string description="");        

    int getCategory() {return category;}
    int getID() {return ID;};
    std::string getName() {return name;};
    int getNumElements() {return numElements;};
    std::string getDesc() {return description;};
    
    // describe command
    std::string toString();
};
}
#endif

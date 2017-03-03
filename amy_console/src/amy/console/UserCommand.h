#ifndef __AMY_CONSOLE_USERCOMMAND_H
#define __AMY_CONSOLE_USERCOMMAND_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
// Class to represent user commands.
// Commands are of two types: simple (involve just an action) and complex (involve action and value).
class UserCommand 
{
public:
    /*! command types */
    enum eType
    {
         eCOM_SIMPLE,                      /*! simple command */
         eCOM_COMPLEX,                  /*! complex command */    
    };

private:
    std::string name;              // command name
    int code;                          // numerical code to identify the command
    int type;                           // command type (one of eType) 
    std::string desc;              // command description

public:
    UserCommand();
    UserCommand(std::string name, int code, int type, std::string desc);

    std::string getName() {return name;};
    int getCode() {return code;};
    bool isSimple() {return (type==eCOM_SIMPLE);};    
    bool isComplex() {return (type==eCOM_COMPLEX);};    
    std::string getDescription() {return desc;};
};
}		
#endif

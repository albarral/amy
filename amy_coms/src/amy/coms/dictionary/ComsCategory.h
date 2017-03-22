#ifndef __AMY_COMS_COMSCATEGORY_H
#define __AMY_COMS_COMSCATEGORY_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "amy/coms/dictionary/ComsCommand.h"

namespace amy
{
// Base class to represent categories of communication commands.
 class ComsCategory
{
public:
    /*! command categories */
    enum eCategories
    {
         eCATEGORY_UNDEF,               /*! undefined category */
         eCATEGORY_JOINTS,              /*! command of joint category */
         eCATEGORY_AXIS,                 /*! command of axis category */
         eCATEGORY_CYCLIC,            /*! command of cyclic category */
         eCATEGORY_OTHER,             /*! command of other category */
         eCATEGORY_DIM
    };
        
protected:    
    int ID;                    /*! category ID  */
    std::string name;    /*! category name  */
    std::vector<ComsCommand> listCommands;  /*! list of commands for this category */
    
public:
    ComsCategory();
    ComsCategory(int ID, std::string name);    
    ~ComsCategory();    

    int getID() {return ID;};
    std::string getName() {return name;};
    std::vector<ComsCommand>& getListCommands() {return listCommands;};
    
    // check valid values
    static bool isValidCategory(int value);    
    // describe category
    std::string toString();
    
 protected:
    // builds category with a list of commands
    virtual void build() = 0;

};
}
#endif

#ifndef __AMY_COMS_AMYCOMMAND_H
#define __AMY_COMS_AMYCOMMAND_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
/** 
 * Base class to represent amy commands. Used for communicating with amy from external processes.
 * It involves 3 elements: category, action and value.
 * For its transmission, the command must be converted to textual form.
 * On reception, the textual form is analyzed and the command interpreted.
 */
class AmyCommand
{
public:
    static const std::string separator;
        
protected:    
    int category;   /*! command category  */
    int action;       /*! action to be performed */
    float value;     /*! value applied by the action */
    bool bvalid;     /*! command validity */   
    std::string text;      /*! command textual form */    
    
public:
    AmyCommand();        
    // undefined category, invalid command
    AmyCommand(int action, float value);

    int getCategory() {return category;};
    int getAction() {return action;};
    float getValue() {return value;};
    bool isValidCommand() {return bvalid;}; 
    std::string getText() {return text;};
        
    /*! builds the textual form of the command and returns it */
    std::string buildTextualForm();
    
protected:    
    // describe action 
    virtual std::string describeAction();
};
}
#endif

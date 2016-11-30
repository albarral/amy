#ifndef __AMY_UTILS_FILEWRITER_H
#define __AMY_UTILS_FILEWRITER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/utils/File.h"

namespace amy 
{
class FileWriter : public File
{
private:
    bool bappend;   // append flag (to write from the last line)
    
public:
    FileWriter();
    //~FileWriter();

    void setAppendMode(bool value) {bappend = value;};
    virtual bool open(std::string name);
    void writeLine(std::string);
    void writeFlush(std::string);
    // move writer pointer to file's first byte
    void goTop();
};

}		
#endif

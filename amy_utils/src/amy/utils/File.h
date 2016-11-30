#ifndef __AMY_UTILS_FILE_H
#define __AMY_UTILS_FILE_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <fstream>
#include <string>

namespace amy 
{
class File
{
protected:
    std::fstream file;     
    std::string filename;

public:
    File();
    //~File();

    virtual bool open(std::string name) = 0;
    bool isOpen();
    std::string getName() {return filename;}
    bool close();
};

}		
#endif

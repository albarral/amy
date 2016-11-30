#ifndef __AMY_UTILS_FILEREADER_H
#define __AMY_UTILS_FILEREADER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/utils/File.h"

namespace amy 
{
class FileReader : public File
{
public:
    //FileReader();
    //~FileReader();

    virtual bool open(std::string name);
    std::string readLine();
};

}		
#endif

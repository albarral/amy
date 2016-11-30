/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/utils/FileReader.h"

namespace amy 
{
bool FileReader::open(std::string name)
{
    bool bok = false;
    // proceed if not open yet
    if (!file.is_open())
    {        
        file.open(name, std::fstream::in);
        
        if (file.is_open())
        {
            filename = name;
            bok = true;
        }
    }

    return bok;
}
    
std::string FileReader::readLine()
{
    std::string line;    
    std::getline(file, line);

    return line;
}
}
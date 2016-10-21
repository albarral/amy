/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/utils/Record.h"

namespace amy 
{
Record::Record()
{
    magnitude1 = "";
    magnitude2 = "";
    timeUnit = "ms";
}

void Record::reset()
{
    // clears record list & starts chrono
    listRecords.clear();
    oClick.start();
}

void Record::addElement(float value1, float value2)
{
    // reads passed time
    oClick.read();
    
    // builds a record element & stores it in the list
    recordElement record;
    record.val1 = value1;
    record.val2 = value2;
    record.time = oClick.getMillis();
    
    listRecords.push_back(record);
}

void Record::findRecordLimits()
{
    maxValue = minValue = 0.0;
    // track min and max values
    for (recordElement& element : listRecords)
    {
        if (element.val1 > maxValue)
            maxValue = element.val1;
        else if (element.val1 < minValue)                        
            minValue = element.val1;
    }
    // get time of last element
    recordElement& last = listRecords.back();
    maxTime = last.time;
}

 std::string Record::toString()
 {     
    std::string desc = "record: [\n";
    for (recordElement& element : listRecords)
    {
        desc += "(" + std::to_string(element.val1) + ", " + std::to_string(element.val2) + ", " + std::to_string(element.time) + ")\n"; 
    }     
    desc += "]\n";
    
    return desc;
 }
 
}
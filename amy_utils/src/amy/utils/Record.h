#ifndef _AMY_UTILS_RECORD_H
#define _AMY_UTILS_RECORD_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *

 ***************************************************************************/

#include <string>
#include <vector>
#include "amy/utils/Click.h"

namespace amy 
{
struct recordElement
{
    float val1;
    float val2;
    int time;        
};
// Utility class for storing temporal records (2 magnitudes), The time value is automatically set (in ms)
class Record
{
private:
    std::vector<recordElement> listRecords; // records list
    std::string magnitude1;  // name of magnitude 1
    std::string magnitude2;  // name of magnitude 2
    std::string timeUnit;   // time units (ms)
    Click oClick;   
    float maxValue;    // max of magnitude 1
    float minValue;    // min of magnitude 1
    int maxTime;        // time of last element  

public:

    Record();
    
    void setMagnitudes(std::string magnitude1, std::string magnitude2 = "");
    std::string getMagnitude1() {return magnitude1;}
    std::string getMagnitude2()  {return magnitude2;};
    
    // RECORD WRITING ...
    // resets the record
    void reset();
    // adds one element (with single or dual magnitude)
    void addElement(float value1, float value2=0.0);

    // RECORD ANALYSING ...
    // access records list
    std::vector<recordElement>& getRecords() {return listRecords;};
    // get record size
    int getSize() {return listRecords.size();};
    // search limit values of all magnitudes
    void findRecordLimits();
    // access the limits
    float getMaxValue1() {return maxValue;};
    float getMinValue1() {return minValue;};
    int getMaxTime() {return maxTime;};
    
    // show record elements
    std::string toString();
};
}

#endif

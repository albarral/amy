#ifndef __AMY_ROBOTS_JOINT_H
#define __AMY_ROBOTS_JOINT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
// Class to represent an arm's joint. 
class Joint
{
private:
    std::string name;   // joint name
    int limit1;      // lower allowed angle (degrees)
    int limit2;      // upper allowed angle (degrees)

public:
    
    Joint();
    ~Joint();

    void setName(std::string value) {name = value;};
    std::string getName() {return name;};

    void setLimits(int lowLimit, int highLimit);        
    int getLowerLimit() {return limit1;}
    int getUpperLimit() {return limit2;}
};
}
#endif

#ifndef __AMY_CORE_JOINT_H
#define __AMY_CORE_JOINT_H

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
public:    
    // joint types
    enum eTypes
    {
        eJOINT_HS,
        eJOINT_VS,
        eJOINT_ELB,
        eJOINT_HW,
        eJOINT_VW,
        eJOINT_DIM
    };
    // joint names
    static const std::string hshoulder;
    static const std::string vshoulder;
    static const std::string elbow;
    static const std::string hwrist;
    static const std::string vwrist;

private:
    int type;               // joint type (one of eTypes)
    std::string name;   // joint name
    int limit1;      // lower allowed angle (degrees)
    int limit2;      // upper allowed angle (degrees)

public:
    
    Joint();
    ~Joint();

    void setType(int value);
    int getType() {return type;};
    std::string getName() {return name;};

    void setLimits(int lowLimit, int highLimit);        
    int getLowerLimit() {return limit1;}
    int getUpperLimit() {return limit2;}

    static bool isValidType(int value);
    static std::string getName4Type(int value);
    
    // return joint description
    std::string toString();
};
}
#endif

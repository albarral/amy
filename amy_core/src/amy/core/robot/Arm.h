#ifndef __AMY_CORE_ARM_H
#define __AMY_CORE_ARM_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "amy/core/robot/Joint.h"

namespace amy
{
// Class to represent a robot's arm.
class Arm
{
public:
    // arm types
    enum eType
    {
        eLEFT_ARM,
        eRIGHT_ARM,
        eSINGLE_ARM,
        eUNDEF_ARM
    };
    // arm axes
    enum eAxes
    {
        eAXIS_PAN,
        eAXIS_TILT,
        eAXIS_RADIAL,
        eAXIS_DIM
    };
    // axes names
    static const std::string pan;
    static const std::string tilt;
    static const std::string radial;
    
private:
    std::string name;   // arm name
    int type;                // arm type (one of eTypes)   
    std::vector<Joint> listJoints;
protected:    
    // segments
    int lenHumerus; // length of arm's humerus (cm)        
    int lenRadius; // length of arm's radius (cm)        
   
public:    
    Arm();
    ~Arm();

    void setName(std::string value) {name = value;};
    std::string getName() {return name;};
    
    void setType(int value) {type = value;};
    int getType() {return type;};

    // reset joints
    void reset();
    // get joints list
    std::vector<Joint>& getListJoints() {return listJoints;};
    // gets number of joints
    int getNumJoints() {return listJoints.size();};

    // checks if the arm has the given joint
    bool hasJoint(int jointType);
    // get specific joint by position
    Joint* getJointByPos(int pos);
    // get specific joint by type
    Joint* getJointByType(int jointType);
    
    int getLenHumerus() {return lenHumerus;};            
    int getLenRadius() {return lenRadius;};                

    static bool isValidAxis(int value);
    static std::string getName4Axis(int axis);
    
    // return arm description
    std::string toString();
    
protected:
    // add a new joint
    void addJoint(Joint& oJoint);
    
};
}
#endif

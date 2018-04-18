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
    static const std::string horizontal_shoulder;
    static const std::string vertical_shoulder;
    static const std::string elbow;
    static const std::string horizontal_wrist;
    static const std::string vertical_wrist;
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
    
private:
    std::string name;   // arm name
    int type;
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
    bool hasJoint(std::string jointName);
    // get specific joint by position
    Joint* getJointByPos(int pos);
    // get specific joint by name
    Joint* getJointByName(std::string jointName);
    
    int getLenHumerus() {return lenHumerus;};            
    int getLenRadius() {return lenRadius;};                

    // return arm description
    std::string toString();
    
protected:
    // add a new joint
    void addJoint(Joint& oJoint);
    
};
}
#endif

#ifndef __AMY_MOVE_MOVEGROUP_H
#define __AMY_MOVE_MOVEGROUP_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "amy/move/data/Movement.h"

namespace amy
{
// Class that represents a group of arm movements. 
class MoveGroup
{
private:
    std::string name;
    std::vector<Movement> listMovements;
    int intensity;
   
public:    
    MoveGroup();
    ~MoveGroup();

    void reset();

    void setName(std::string value) {name = value;};
    std::string getName() {return name;};

    void updateIntensity(float value);    
    float getIntensity() {return intensity;}        
    // recomputes all movements in the list
    void compute();

    // add a new movement to the group
    void addMovement(Movement& oMovement);
    // get list of movements
    std::vector<Movement>& getListMovements() {return listMovements;};
    
    std::string getDescription();        
};
}
#endif

#ifndef __AMY_MOVEMENT_H
#define __AMY_MOVEMENT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "amy/arm/data/MoveStep.h"

namespace amy
{
// Class that represents an arm movement, a sequence of move steps which define a complex arm trajectory.
class Movement
{
private:
    int ID;
    std::string name;
    bool bcomputed; // indicates all move steps are computed
    int vmax;
    std::vector<MoveStep> listMoveSteps;
   
public:    
    Movement();
    ~Movement();

    void reset();

    void setID(int value) {ID = value;};
    void setName(std::string value) {name = value;};

    void setComputed(bool value) {bcomputed = value;};
    bool isComputed() {return bcomputed;}

    void setMaxSpeed(int value) {vmax = value;};    
    int getMaxSpeed() {return vmax;}
    // updates all movement steps with the movement max speed (they'll need recomputation)
    void propagateSpeed2Steps();

    // add a new move step
    void addMoveStep(MoveStep& oMoveStep);
    // get list of move steps
    std::vector<MoveStep>& getListMoveSteps() {return listMoveSteps;};
    
        
};
}
#endif

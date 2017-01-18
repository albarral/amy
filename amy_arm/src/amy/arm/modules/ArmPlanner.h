#ifndef __AMY_ARM_ARMPLANNER_H
#define __AMY_ARM_ARMPLANNER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/data/Movement.h"

namespace amy
{
// Class used to build predefined arm movements through sequences of simple move steps (MoveStep).
// This movements will be decoded and performed by the ArmMover module.    .
    
class ArmPlanner
{
public:    
   // builds a movement that mimics a "pajarita"
   static void buildPajaritaMovement(Movement& oMovement);
   
   // more to be defined
};
}
#endif

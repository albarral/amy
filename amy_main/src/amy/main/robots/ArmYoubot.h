#ifndef __AMY_MAIN_ARMYOUBOT_H
#define __AMY_MAIN_ARMYOUBOT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/core/robot/Arm.h"

namespace amy
{
// Arm version for Kuka's Youbot robot
class ArmYoubot : public Arm
{
    public:
        ArmYoubot();
};

}

#endif

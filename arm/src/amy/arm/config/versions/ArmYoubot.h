#ifndef __AMY_ARM_ARMYOUBOT_H
#define __AMY_ARM_ARMYOUBOT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/config/ArmVersion.h"

namespace amy
{
// Arm version for Kuka's Youbot robot
class ArmYoubot : public ArmVersion
{
    public:
        ArmYoubot();
};

}

#endif

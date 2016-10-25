/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/arm/data/MoveStep3D.h"
#include "amy/arm/modules/JointMover2.h"

namespace amy
{
MoveStep3D::MoveStep3D ()
{
    zangle = 0;   
    //zmove = JointMover::eMOV_STOP; 
    vz = 0;
}

//MoveStep3D::MoveStep3D(int angle, int tics, int maxSpeed)
//{
//    // TO DO ...
//}

}

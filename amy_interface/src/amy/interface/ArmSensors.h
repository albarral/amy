#ifndef __AMY_INTERFACE_ARM_ARMSENSORS_H
#define __AMY_INTERFACE_ARM_ARMSENSORS_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace amy
{
// Definition of arm sensor structures
    
struct JointsData
{
    float hs; 
    float vs; 
    float elb; 
    float hwri; 
    float vwri;   
};

struct AxesData
{
    float pan; 
    float tilt; 
    float radial; 
};

}
#endif

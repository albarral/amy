#ifndef __AMY_SHOW_SHOWDATA_H
#define __AMY_SHOW_SHOWDATA_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


namespace amy
{
class ShowData
{
public:    
    // data
    float pan;
    float tilt;
    float radius;
    float angleVS;
    float angleELB;
    int stateHS;    // HS driver state
    int stateVS;    // VS driver state
    int stateELB;   // ELB driver state
    float panSOSpeed;
    float panCOSpeed;
    float tiltSOSpeed;
    float tiltCOSpeed;    
    
public:
  ShowData();
  ~ShowData();
};
}		

#endif

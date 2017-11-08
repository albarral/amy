/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/ComsData.h"

namespace amy
{
ComsData::ComsData() 
{
}

ComsData::~ComsData()
{
    reset();
}

void ComsData::addSpecialAction(int action)
{
    std::lock_guard<std::mutex> locker(mutex);
    
    listSpecialActions.push_back(action);
}

void ComsData::reset()
{
    std::lock_guard<std::mutex> locker(mutex);
    
    listSpecialActions.clear();    
}

std::vector<int> ComsData::getListSpecialActions()
{
    std::lock_guard<std::mutex> locker(mutex);
    
    return listSpecialActions;    
}

bool ComsData::hasPendingActions()
{
    std::lock_guard<std::mutex> locker(mutex);

    return !(listSpecialActions.empty());        
}
}		

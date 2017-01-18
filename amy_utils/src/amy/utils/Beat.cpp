/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/utils/Beat.h"

namespace amy
{
// Constructor
Beat::Beat ()
{    
    reset();
}

void Beat::reset()
{
    std::lock_guard<std::mutex> locker(mutex);

    tics = 0;
    banomaly = false;
    alert = "";
}

void Beat::tic()
{  
    std::lock_guard<std::mutex> locker(mutex);
    tics++;
}

int Beat::getTics()
{
    std::lock_guard<std::mutex> locker(mutex);
    return tics;
}

void Beat::informAnomaly(std::string text)
{
    std::lock_guard<std::mutex> locker(mutex);
    banomaly = true;
    alert = text;    
}

void Beat::removeAnomaly()
{
    std::lock_guard<std::mutex> locker(mutex);
    banomaly = false;
    alert = "";    
}

bool Beat::hasAnomaly()
{
    std::lock_guard<std::mutex> locker(mutex);
    return banomaly;
}

std::string Beat::getAlert()
{
    std::lock_guard<std::mutex> locker(mutex);
    return alert;
}

std::string Beat::toString()
{
    std::string text = "Beat[ tics = " + std::to_string(tics) + 
         ", anomaly = " + std::to_string(banomaly) +
         ", alert = " + alert + "]\n";

    return text;
}

}

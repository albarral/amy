#ifndef __AMY_UTILS_BEAT_H
#define __AMY_UTILS_BEAT_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include <string>

namespace amy
{
// Class used to sense the life of modules. Thread safe.
class Beat
{
    private:        
        std::mutex mutex;
        int tics;
        bool banomaly;
        std::string alert;

public:
        Beat();
        //~Beat();
        
        // resets all values
        void reset();
        
        // increment the tics
        void tic();
        int getTics();
        
        // inform of an anomaly (raise flag and set alert text)
        void informAnomaly(std::string text);
        // remove anomaly (lower flag and remove alert text)
        void removeAnomaly();
        
        // check if beat has an anomaly
        bool hasAnomaly();
        // get the alert text
        std::string getAlert();
        
        std::string toString();        
};

}    
#endif

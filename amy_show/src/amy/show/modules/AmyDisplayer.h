#ifndef __AMY_SHOW_AMYDISPLAYER_H
#define __AMY_SHOW_AMYDISPLAYER_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <amy/utils/module3.h>
#include "amy/show/SharedDisplay.h"

namespace amy
{
// Module used to plot the evolution of arm signals (for debugging purpose).
// It gets the info from the arm bus.
class AmyDisplayer : public Module3
{
private:
    SharedDisplay* pSharedDisplay;      // pointer to shared display (used to avoid X11 problems with different threads)

public:
    AmyDisplayer();
    ~AmyDisplayer();

    void shareDisplay(SharedDisplay& oSharedDisplay);
    
private:
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
};
}		
#endif

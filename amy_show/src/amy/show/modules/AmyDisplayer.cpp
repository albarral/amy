/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/modules/AmyDisplayer.h"

namespace amy
{
// Constructor 
AmyDisplayer::AmyDisplayer()
{    
    modName = "AmyDisplayer";
    pSharedDisplay = 0;
 }

AmyDisplayer::~AmyDisplayer()
{
}

void AmyDisplayer::shareDisplay(SharedDisplay& oSharedDisplay)
{
    pSharedDisplay = &oSharedDisplay;    
}

void AmyDisplayer::first()
{
}
                    
// drives the axis towards the target position
void AmyDisplayer::loop()
{
    // show window
    if (pSharedDisplay != 0)
    {    
        pSharedDisplay->show();
    }
}

}
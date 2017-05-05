#ifndef __AMY_COMS_CYCLICCLIENT_H
#define __AMY_COMS_CYCLICCLIENT_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "amy/coms/ifaces/iComsCyclic.h"
#include "amy/coms/data/CyclicCommand.h"


namespace amy
{
// Class used to send requests for cyclic control.
class CyclicClient : public iComsCyclic
{    
private:
    std::string text;
    
public:
    CyclicClient();

    std::string getCommand() {return text;};
    
     // ARM MOVER
    // launch this movement type
    virtual void launchMove(int value);
    // stop movement
    virtual void stopMove();
    // turn the movement these angle (degrees)
    virtual void turnMove(int value);
    // make movement wider/narrower
    virtual void moveWider(bool value);
    // make movement taller/shorter
    virtual void moveTaller(bool value);
    // make movement faster/slower
    virtual void moveFaster(bool value);
    
    // FRONTAL CYCLER
   virtual void frontFrequency(float value);
    virtual void frontAmplitude(float value);
    virtual void frontAngle(float value);
    virtual void frontStart();
    virtual void frontStop();

private:
    // obtains the textual form of the given command
    void updateText(CyclicCommand& oCyclicCommand);
};
}
#endif

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
    
   // front cyclic movements    
    virtual void frontFrequency(float value);
    virtual void frontAmplitude(float value);
    virtual void frontAngle(float value);
    virtual void frontStart();
    virtual void frontStop();
//    // tilt cyclic movements
//    virtual void tiltFrequency(float value);
//    virtual void tiltAmplitude(float value);
//    virtual void tiltTrigger();
//    virtual void tiltStop();

private:
    // obtains the textual form of the given command
    void updateText(CyclicCommand& oCyclicCommand);
};
}
#endif

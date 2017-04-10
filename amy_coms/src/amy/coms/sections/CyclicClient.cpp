/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/coms/sections/CyclicClient.h"
#include "amy/coms/dictionary/CyclicCategory.h"

namespace amy
{

CyclicClient::CyclicClient()
{
    text = "";
}

// set front cyclic frequency
void CyclicClient::frontFrequency(float value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_FRONT_FREQ, value);
    updateText(oCyclicCommand);
}

// set front amplitude (degrees)
void CyclicClient::frontAmplitude(float value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_FRONT_AMP, value);
    updateText(oCyclicCommand);
}

// set front cyclic angle
void CyclicClient::frontAngle(float value)
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_FRONT_ANGLE, value);
    updateText(oCyclicCommand);
}

// start front cyclic movement
void CyclicClient::frontStart()
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_FRONT_START);
    updateText(oCyclicCommand);
}

// stop front cyclic movement
void CyclicClient::frontStop()
{
    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_FRONT_STOP);
    updateText(oCyclicCommand);
}

//void CyclicClient::tiltFrequency(float value)
//{
//    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_TILT_FREQ, value);
//    updateText(oCyclicCommand);
//}
//
//// set tilt amplitude (degrees)
//void CyclicClient::tiltAmplitude(float value)
//{
//    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_TILT_AMP, value);
//    updateText(oCyclicCommand);
//}
//
//// trigger tilt cyclic movement
//void CyclicClient::tiltTrigger()
//{
//    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_TILT_TRIGGER);
//    updateText(oCyclicCommand);
//}
//
//// stop tilt cyclic movement
//void CyclicClient::tiltStop()
//{
//    CyclicCommand oCyclicCommand(CyclicCategory::eCYCLIC_TILT_STOP);
//    updateText(oCyclicCommand);
//}

void CyclicClient::updateText(CyclicCommand& oCyclicCommand)
{       
    // if valid command, build textual form
    if (oCyclicCommand.isValidCommand())
    {
        text = oCyclicCommand.buildTextualForm();
    }        
    // otherwise clean text
    else
        text = "";
}

}
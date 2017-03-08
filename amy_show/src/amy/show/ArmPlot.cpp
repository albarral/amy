/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/ArmPlot.h"

namespace amy 
{
ArmPlot::ArmPlot()
{
    handColor = cv::Scalar(0, 255, 255);  // yellow
    elbowColor = cv::Scalar(255, 255, 255);  // white        
    
    // set default values (20 + 20 arm, window side 200)
    lenHum = 20;
    lenRad = 20;
    maxLen = lenHum + lenRad + 5;
    maxSide = 200;    
}

    
void ArmPlot::setArmSize(int lenH, int lenR)
{    
    // assure valid values
    if ((lenH > 0) && (lenR > 0))
    {
        lenHum = lenH;
        lenRad = lenR;        
        maxLen = lenHum + lenRad + 5;
    }
}

}
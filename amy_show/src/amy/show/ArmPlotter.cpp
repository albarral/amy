/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/ArmPlotter.h"

namespace amy
{
// Constructor 
ArmPlotter::ArmPlotter()
{    
    modName = "ArmPlotter";
    bconnected = false;
    pArmBus = 0;
 }

ArmPlotter::~ArmPlotter()
{
    // hide window
    oArmPlot.hide();        
}

void ArmPlotter::connect(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;    
    bconnected = true;
}

void ArmPlotter::first()
{
    // set plot sizes
    int w = 400;
    int h = 200;
    oArmPlot.setPlot(w, h, 20, w/2, "arm 1");
}
                    
// drives the axis towards the target position
void ArmPlotter::loop()
{
    senseBus();
    // draw arm pos
    oArmPlot.drawArmPosition(pan, tilt, 0);
    oArmPlot.show();    
}

void ArmPlotter::senseBus()
{
    pan = pArmBus->getSO_ARM_PAN().getValue();
    tilt = pArmBus->getSO_ARM_TILT().getValue();    
}


}
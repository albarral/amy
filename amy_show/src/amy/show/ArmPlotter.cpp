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
    pVSBus = 0;
 }

ArmPlotter::~ArmPlotter()
{
    // hide windows
    oArmFrontView.hide();        
    //oArmFrontView2.hide();        
}

void ArmPlotter::connect(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;
    pVSBus = &pArmBus->getBusVS();    
    bconnected = true;
}

void ArmPlotter::first()
{
    // set plot sizes
    int w = 400;
    int h = 200;
    oArmFrontView.setPlotSize(w, h, "arm front");
    // display pan range [-200, 200] and tilt range [-20, 120]  
    oArmFrontView.setRanges(-200, 200, -20, 120);
}
                    
// drives the axis towards the target position
void ArmPlotter::loop()
{
    senseBus();
    // draw arm pos
    oArmFrontView.drawArmPosition(pan, tilt, 0, vsAngle);
    oArmFrontView.show();    
}

void ArmPlotter::senseBus()
{
    pan = pArmBus->getSO_ARM_PAN().getValue();
    tilt = pArmBus->getSO_ARM_TILT().getValue();    
    vsAngle = pVSBus->getSO_IST_ANGLE().getValue();
}


}
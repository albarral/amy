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
    pELBus = 0;
 }

ArmPlotter::~ArmPlotter()
{
    // hide windows
    oArmFrontView.hide();        
    oArmSideView.hide();        
}

void ArmPlotter::connect(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;
    pVSBus = &pArmBus->getBusVS();    
    pELBus = &pArmBus->getBusEL();    
    bconnected = true;
}

void ArmPlotter::first()
{
    // frontal arm view (200 pixels wide)
    oArmFrontView.setArmSize(40, 40);
    oArmFrontView.configDraw("arm frontal", 200);

    // side arm view (200 pixels wide)
    oArmSideView.setArmSize(40, 40);
    oArmSideView.configDraw("arm side", 200);
}
                    
// drives the axis towards the target position
void ArmPlotter::loop()
{
    senseBus();
    // draw arm frontal view
    oArmFrontView.drawArm(pan, tilt, 0, vsAngle);
    oArmFrontView.show();    
    // draw arm side view
    int lenH = 40;
    int lenR = 40;
    oArmSideView.drawArm(vsAngle, elbAngle, lenH, lenR);
    oArmSideView.show();    
}

void ArmPlotter::senseBus()
{
    pan = pArmBus->getSO_ARM_PAN().getValue();
    tilt = pArmBus->getSO_ARM_TILT().getValue();    
    vsAngle = pVSBus->getSO_IST_ANGLE().getValue();
    elbAngle = pELBus->getSO_IST_ANGLE().getValue();
}


}
/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/modules/ArmPlotter.h"

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
    // should be read from config
    int lenH = 40;
    int lenR = 40;
    // frontal arm view (200 pixels wide)
    oArmFrontView.setArmSize(lenH, lenR);
    oArmFrontView.configDraw("arm frontal", 200);

    // side arm view (200 pixels wide)
    oArmSideView.setArmSize(lenH, lenR);
    oArmSideView.configDraw("arm side", 200);
}
                    
// drives the axis towards the target position
void ArmPlotter::loop()
{
    senseBus();
    // draw arm frontal view
    oArmFrontView.drawArm(vsAngle, pan, tilt, radius);
    oArmFrontView.show();    
    // draw arm side view
    oArmSideView.drawArm(vsAngle, elbAngle);
    oArmSideView.show();    
}

void ArmPlotter::senseBus()
{
    pan = pArmBus->getPanBus().getSO_AXIS_POS().getValue();
    tilt = pArmBus->getTiltBus().getSO_AXIS_POS().getValue();    
    radius = pArmBus->getRadialBus().getSO_AXIS_POS().getValue();
    vsAngle = pVSBus->getSO_IST_ANGLE().getValue();
    elbAngle = pELBus->getSO_IST_ANGLE().getValue();
}


}
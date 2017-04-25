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
    pHSBus = 0;
    pVSBus = 0;
    pELBus = 0;
    pSharedDisplay = 0;
 }

ArmPlotter::~ArmPlotter()
{
}

void ArmPlotter::connect(ArmBus& oArmBus)
{
    pArmBus = &oArmBus;
    pHSBus = &oArmBus.getBusHS();    
    pVSBus = &oArmBus.getBusVS();    
    pELBus = &oArmBus.getBusEL();    
    bconnected = true;
}

void ArmPlotter::shareDisplay(SharedDisplay& oSharedDisplay)
{
    pSharedDisplay = &oSharedDisplay;    
}

void ArmPlotter::first()
{
    // should be read from config
    int lenH = 40;
    int lenR = 40;
    // frontal arm view
    oArmFrontView.setArmSize(lenH, lenR);
    oArmFrontView.configDraw("arm frontal", pSharedDisplay->getDisplayUpW(), pSharedDisplay->getDisplayUpH());
    // side arm view
    oArmSideView.setArmSize(lenH, lenR);
    oArmSideView.configDraw("arm side", pSharedDisplay->getDisplayUpW(), pSharedDisplay->getDisplayUpH());
    // joint limits
    int w = pSharedDisplay->getDisplayBotW();
    int h = pSharedDisplay->getDisplayBotH();
    oHSDiscPlot.initPlot(w, h, "HS");
    oHSDiscPlot2.initPlot(w, h, "VS");
    oHSDiscPlot3.initPlot(w, h, "ELB");
}
                    
// drives the axis towards the target position
void ArmPlotter::loop()
{
    senseBus();
    // draw arm frontal view
    oArmFrontView.drawArm(angleVS, pan, tilt, radius);
    // draw arm side view
    oArmSideView.drawArm(angleVS, angleELB);
    // draw joint limits
    oHSDiscPlot.drawDisc(limitHS==0);
    oHSDiscPlot2.drawDisc(limitVS==0);
    oHSDiscPlot3.drawDisc(limitELB==0);
        
    // show windows
    if (pSharedDisplay != 0)
    {
        // copy the frontal view to the display (up1 window)
        pSharedDisplay->updateDisplayUp1(oArmFrontView.getImage());
        // copy the side view to the display (up2 window)
        pSharedDisplay->updateDisplayUp2(oArmSideView.getImage());
        // copy joint states to display (bottom windows)
        pSharedDisplay->updateDisplayBot(0, oHSDiscPlot.getImage());
        pSharedDisplay->updateDisplayBot(1, oHSDiscPlot2.getImage());
        pSharedDisplay->updateDisplayBot(2, oHSDiscPlot3.getImage());
    }
}

void ArmPlotter::senseBus()
{
    // axis positions
    pan = pArmBus->getPanBus().getSO_AXIS_POS().getValue();
    tilt = pArmBus->getTiltBus().getSO_AXIS_POS().getValue();    
    radius = pArmBus->getRadialBus().getSO_AXIS_POS().getValue();
    // joint positions
    angleVS = pVSBus->getSO_IST_ANGLE().getValue();
    angleELB = pELBus->getSO_IST_ANGLE().getValue();
    // joint limits
    limitHS = pHSBus->getSO_JOINT_LIMIT_REACHED().getValue(); 
    limitVS = pVSBus->getSO_JOINT_LIMIT_REACHED().getValue(); 
    limitELB = pELBus->getSO_JOINT_LIMIT_REACHED().getValue(); 
}


}
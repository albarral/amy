/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/modules/ArmPlotter.h"
#include "amy/arm/modules/JointDriver.h"

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
    // discs for joint driver states
    int w = pSharedDisplay->getDisplayBotW();
    int h = pSharedDisplay->getDisplayBotH();
    oDiscPlot1.initPlot(w, h, "HS");
    oDiscPlot2.initPlot(w, h, "VS");
    oDiscPlot3.initPlot(w, h, "ELB");
}
                    
// drives the axis towards the target position
void ArmPlotter::loop()
{
    senseBus();
    // draw arm frontal view
    oArmFrontView.drawArm(angleVS, pan, tilt, radius);
    // draw arm side view
    oArmSideView.drawArm(angleVS, angleELB);
    // draw joint driver states
    oDiscPlot1.drawDisc(driverState2DiscColor(stateHS));
    oDiscPlot2.drawDisc(driverState2DiscColor(stateVS));
    oDiscPlot3.drawDisc(driverState2DiscColor(stateELB));
        
    // show windows
    if (pSharedDisplay != 0)
    {
        // copy the frontal view to the display (up1 window)
        pSharedDisplay->updateDisplayUp1(oArmFrontView.getImage());
        // copy the side view to the display (up2 window)
        pSharedDisplay->updateDisplayUp2(oArmSideView.getImage());
        // copy joint states to display (bottom windows)
        pSharedDisplay->updateDisplayBot(0, oDiscPlot1.getImage());
        pSharedDisplay->updateDisplayBot(1, oDiscPlot2.getImage());
        pSharedDisplay->updateDisplayBot(2, oDiscPlot3.getImage());
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
    stateHS = pHSBus->getSO_DRIVER_STATE().getValue(); 
    stateVS = pVSBus->getSO_DRIVER_STATE().getValue(); 
    stateELB = pELBus->getSO_DRIVER_STATE().getValue(); 
}

int ArmPlotter::driverState2DiscColor(int driveState)
{
    int disc;
    switch (driveState) 
    {
        case JointDriver::eSTATE_DONE:
            disc = DiscPlot::eSTATE_RED;
            break;
        case JointDriver::eSTATE_MOVE:
            disc = DiscPlot::eSTATE_GREEN;
            break;
        case JointDriver::eSTATE_BRAKE:
            disc = DiscPlot::eSTATE_YELLOW;
            break;
        default:
            disc = DiscPlot::eSTATE_GREY;            
    }
    return disc;
}
}
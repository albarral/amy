/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/show/plot/ArmPlotter.h"

namespace amy
{
// Constructor 
ArmPlotter::ArmPlotter()
{    
 }

//ArmPlotter::~ArmPlotter()
//{
//}

void ArmPlotter::init(tivy::SharedDisplay& oSharedDisplay)
{
    // should be read from config
    int lenH = 40;
    int lenR = 40;
    // frontal arm view
    oArmFrontView.setArmSize(lenH, lenR);
    oArmFrontView.configDraw("arm frontal", oSharedDisplay.getDisplayUpW(), oSharedDisplay.getDisplayUpH());
    // side arm view
    oArmSideView.setArmSize(lenH, lenR);
    oArmSideView.configDraw("arm side", oSharedDisplay.getDisplayUpW(), oSharedDisplay.getDisplayUpH());
    // discs for joint driver states
    int w = oSharedDisplay.getDisplayBotW();
    int h = oSharedDisplay.getDisplayBotH();
    oDiscPlot1.initPlot(w, h, "HS");
    oDiscPlot2.initPlot(w, h, "VS");
    oDiscPlot3.initPlot(w, h, "ELB");
}
                    
// drives the axis towards the target position
void ArmPlotter::draw(tivy::SharedDisplay& oSharedDisplay, ShowData* pShowData)
{    
    DataBlockJoints& oDataBlockJoints = pShowData->getDataBlockJoints();
    //DataBlockJointDrivers& oDataBlockJointDrivers = pShowData->getDataBlockJointDrivers();
    DataBlockAxes& oDataBlockAxes = pShowData->getDataBlockAxes();   
    
    // axis positions
    pan = oDataBlockAxes.getPan();
    tilt = oDataBlockAxes.getTilt();    
    radius = oDataBlockAxes.getRadius();
    // joint positions
    angleVS = oDataBlockJoints.getPosVS();
    angleELB = oDataBlockJoints.getPosEL();
    // joint limits
//    stateHS = pHSBus->getSO_DRIVER_STATE().getValue(); 
//    stateVS = pVSBus->getSO_DRIVER_STATE().getValue(); 
//    stateELB = pELBus->getSO_DRIVER_STATE().getValue(); 

    // draw arm frontal view
    oArmFrontView.drawArm(angleVS, pan, tilt, radius);
    // draw arm side view
    oArmSideView.drawArm(angleVS, angleELB);
    // draw joint driver states
    oDiscPlot1.drawDisc(driverState2DiscColor(stateHS));
    oDiscPlot2.drawDisc(driverState2DiscColor(stateVS));
    oDiscPlot3.drawDisc(driverState2DiscColor(stateELB));
        
    // show windows
    // copy the frontal view to the display (up1 window)
    oSharedDisplay.updateDisplayUp1(oArmFrontView.getImage());
    // copy the side view to the display (up2 window)
    oSharedDisplay.updateDisplayUp2(oArmSideView.getImage());
    // copy joint states to display (bottom windows)
    oSharedDisplay.updateDisplayBot(0, oDiscPlot1.getImage());
    oSharedDisplay.updateDisplayBot(1, oDiscPlot2.getImage());
    oSharedDisplay.updateDisplayBot(2, oDiscPlot3.getImage());
}

int ArmPlotter::driverState2DiscColor(int driveState)
{
    int disc;
    switch (driveState) 
    {
        case 0:
            disc = tivy::DiscPlot::eSTATE_RED;
            break;
        case 1:
            disc = tivy::DiscPlot::eSTATE_GREEN;
            break;
        case 2:
            disc = tivy::DiscPlot::eSTATE_YELLOW;
            break;
        default:
            disc = tivy::DiscPlot::eSTATE_GREY;            
    }
    return disc;
}
}
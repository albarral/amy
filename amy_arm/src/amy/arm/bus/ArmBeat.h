#ifndef __AMY_ARM_ARMBEAT_H
#define __AMY_ARM_ARMBEAT_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "amy/utils/Beat.h"

namespace amy
{
// Class used to hold the Beats of all amy_arm modules.
// Each module must have its associated Beat. 
// It can be used to check:
// - which modules are alive
// - which modules work well and which ones have anomalies
class ArmBeat
{
    private:               
        Beat oArmPannerBeat;    // Beat for ArmPanner module
        Beat oArmExtenderBeat;    // Beat for ArmExtender module
        
        Beat oHSBeat;    // HS: horizontal shoulder 
        Beat oVSBeat;   // VS: vertical shoulder 
        Beat oELBeat;    // EL: elbow 
        Beat oHWBeat;   // HW: horizontal wrist
        Beat oVWBeat;   // VW: vertical wrist
        
    public:
        //ArmBeat();
        //~ArmBeat();

        Beat& getArmPannerBeat() {return oArmPannerBeat;}; 
        Beat& getArmExtenderBeat() {return oArmExtenderBeat;}; 
        
        // beats for joint control modules
        Beat& getHSBeat() {return oHSBeat;};
        Beat& getVSBeat() {return oVSBeat;};
        Beat& getELBeat() {return oELBeat;};
        Beat& getHWBeat() {return oHWBeat;};
        Beat& getVWBeat() {return oVWBeat;};

        std::string toString();
};

}    
#endif

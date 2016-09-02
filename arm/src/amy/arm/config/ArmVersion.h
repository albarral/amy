#ifndef __AMY_ARM_ARMVERSION_H
#define __AMY_ARM_ARMVERSION_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
// Base class for definitions of arm versions (with their specific features)
class ArmVersion 
{
    protected:                
        std::string robotName;
        int numJoints;
        // horizontal shoulder
        bool bHS;   // presence 
        int lowerHS; // lower limit (degrees) 
        int upperHS; // upper limit (degrees) 
        // vertical shoulder
        bool bVS;   // presence 
        int lowerVS;  // lower limit (degrees) 
        int upperVS; //  upper limit (degrees)
        // elbow
        bool bEL;     // presence 
        int lowerEL; // lower limit (degrees) 
        int upperEL; // upper limit (degrees) 
        // horizontal wrist
        bool bHW;   // presence 
        int lowerHW; // lower limit (degrees) 
        int upperHW; // upper limit (degrees) 
        // vertical wrist
        bool bVW;   // presence 
        int lowerVW;  // lower limit (degrees) 
        int upperVW; //  upper limit (degrees)
        int len; // length of arm section (cm)        
        
    public:
        ArmVersion();

        bool hasHS() {return bHS;};
        int getHSlower() {return lowerHS;};
        int getHSupper() {return upperHS;};

        bool hasVS() {return bVS;};
        int getVSlower() {return lowerVS;};
        int getVSupper() {return upperVS;};

        bool hasEL() {return bEL;};
        int getELlower() {return lowerEL;};
        int getELupper() {return upperEL;};

        bool hasHW() {return bHW;};
        int getHWlower() {return lowerHW;};
        int getHWupper() {return upperHW;};

        bool hasVW() {return bVW;};
        int getVWlower() {return lowerVW;};
        int getVWupper() {return upperVW;};

        int getLen() {return len;};        
};

}

#endif

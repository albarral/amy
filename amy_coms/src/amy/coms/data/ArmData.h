#ifndef __AMY_COMS_ARMDATA_H
#define __AMY_COMS_ARMDATA_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
// Class used to transfer data of an arm's joints (control and measured values).
class ArmData
{
public:
    static const int numJoints = 5; // num joints in soll & ist messages
    
    private:
        // (commanded) soll angles of joints 1 to 5
        float sollHS;    
        float sollVS;    
        float sollEL;    
        float sollHW;    
        float sollVW;    
        // (measured) ist angles of joints 1 to 5
        float istHS;     
        float istVS;      
        float istEL;     
        float istHW;     
        float istVW;     

    public:
        // reset values for all joints
        void reset();        
        // set soll (commanded) values for each joint
        void setSollHS(float value) {sollHS = value;}
        void setSollVS(float value) {sollVS = value;}
        void setSollEL(float value) {sollEL = value;}
        void setSollHW(float value) {sollHW = value;}
        void setSollVW(float value) {sollVW = value;}        
        // gets soll (commanded) values for all joints
        float getSollHS() {return sollHS;};        
        float getSollVS() {return sollVS;};        
        float getSollEL() {return sollEL;};        
        float getSollHW() {return sollHW;};        
        float getSollVW() {return sollVW;};                
        // set ist (measured) values for each joint
        void setIstHS(float value) {istHS = value;}
        void setIstVS(float value) {istVS = value;}
        void setIstEL(float value) {istEL = value;}
        void setIstHW(float value) {istHW = value;}
        void setIstVW(float value) {istVW = value;}        
        // get ist (measured) values for each joint
        float getIstHS() {return istHS;};        
        float getIstVS() {return istVS;};        
        float getIstEL() {return istEL;};        
        float getIstHW() {return istHW;};        
        float getIstVW() {return istVW;};        
        
        // check if specified object has same soll values
        bool sameSollValues(ArmData& oArmData);
        // check if specified object has same ist values        
        bool sameIstValues(ArmData& oArmData);

        // builds a soll message from the existing soll data 
        std::string createSollMessage();
        // extracts the soll data from a given soll message  
        bool processSollMessage(std::string message);
        
        // returns a description of the object
        std::string toString();
        
};

}    
#endif

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
        void setSoll1(float value) {sollHS = value;}
        void setSoll2(float value) {sollVS = value;}
        void setSoll3(float value) {sollEL = value;}
        void setSoll4(float value) {sollHW = value;}
        void setSoll5(float value) {sollVW = value;}        
        // gets soll (commanded) values for all joints
        float getSoll1() {return sollHS;};        
        float getSoll2() {return sollVS;};        
        float getSoll3() {return sollEL;};        
        float getSoll4() {return sollHW;};        
        float getSoll5() {return sollVW;};                
        // set ist (measured) values for each joint
        void setIst1(float value) {istHS = value;}
        void setIst2(float value) {istVS = value;}
        void setIst3(float value) {istEL = value;}
        void setIst4(float value) {istHW = value;}
        void setIst5(float value) {istVW = value;}        
        // get ist (measured) values for each joint
        float getIst1() {return istHS;};        
        float getIst2() {return istVS;};        
        float getIst3() {return istEL;};        
        float getIst4() {return istHW;};        
        float getIst5() {return istVW;};        
        
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

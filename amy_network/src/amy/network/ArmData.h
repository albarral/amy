#ifndef __AMY_ARM_DATA_H
#define __AMY_ARM_DATA_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

namespace amy
{
// This class is used to transfer data of an arm's joints(control and measured values) through the amy's network
class ArmDataN
{
    private:
        // (commanded) soll angles of joints 1 to 5
        float soll1;    
        float soll2;    
        float soll3;    
        float soll4;    
        float soll5;    
        // (measured) ist angles of joints 1 to 5
        float ist1;     
        float ist2;      
        float ist3;     
        float ist4;     
        float ist5;     

    public:
        // reset values for all joints
        void reset();        
        // set soll (commanded) values for each joint
        void setSoll1(float value) {soll1 = value;}
        void setSoll2(float value) {soll2 = value;}
        void setSoll3(float value) {soll3 = value;}
        void setSoll4(float value) {soll4 = value;}
        void setSoll5(float value) {soll5 = value;}        
        // gets soll (commanded) values for all joints
        float getSoll1() {return soll1;};        
        float getSoll2() {return soll2;};        
        float getSoll3() {return soll3;};        
        float getSoll4() {return soll4;};        
        float getSoll5() {return soll5;};                
        // set ist (measured) values for each joint
        void setIst1(float value) {ist1 = value;}
        void setIst2(float value) {ist2 = value;}
        void setIst3(float value) {ist3 = value;}
        void setIst4(float value) {ist4 = value;}
        void setIst5(float value) {ist5 = value;}        
        // get ist (measured) values for each joint
        float getIst1() {return ist1;};        
        float getIst2() {return ist2;};        
        float getIst3() {return ist3;};        
        float getIst4() {return ist4;};        
        float getIst5() {return ist5;};        
        
        // check if specified object has same soll values
        bool sameSollValues(ArmDataN& oArmData);
        // check if specified object has same ist values        
        bool sameIstValues(ArmDataN& oArmData);
        
        // returns a description of the object
        std::string toString();
};

}    
#endif

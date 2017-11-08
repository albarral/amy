#ifndef __AMY_TALK_DATABLOCKJOINTS_H
#define __AMY_TALK_DATABLOCKJOINTS_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "talky/DataBlock.h"
#include "talky/coms/CommandBlock.h"

namespace amy
{
// Class used to transfer data of an arm's joint (control and measured values).
// Uses talky language.
class DataBlockJoints : public talky::DataBlock
{    
   private:
        static log4cxx::LoggerPtr logger;
        // arm joint angles
        float posHS;    
        float posVS;    
        float posEL;    
        float posHW;    
        float posVW;    

    public:
        DataBlockJoints();
        ~DataBlockJoints();
        
        // reset all values
        void resetData();        
        // set pos values for each joint
        void setPosHS(float value) {posHS = value;}
        void setPosVS(float value) {posVS = value;}
        void setPosEL(float value) {posEL = value;}
        void setPosHW(float value) {posHW = value;}
        void setPosVW(float value) {posVW = value;}        
        // gets pos values from each joints
        float getPosHS() {return posHS;};        
        float getPosVS() {return posVS;};        
        float getPosEL() {return posEL;};        
        float getPosHW() {return posHW;};        
        float getPosVW() {return posVW;};                

        // check if specified object has same values
        bool isEqual(DataBlockJoints& oArmJointInfo);

        // reads joint positions from given command block
        bool readBlock(talky::CommandBlock& oCommandBlock);
        // writes joint positions to given command block
        bool writeBlock(talky::CommandBlock& oCommandBlock);
        
        // returns a description of the object
        virtual std::string toString();        
};

}    
#endif
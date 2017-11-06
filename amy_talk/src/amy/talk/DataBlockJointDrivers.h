#ifndef __AMY_TALK_DATABLOCKJOINTLIMITS_H
#define __AMY_TALK_DATABLOCKJOINTLIMITS_H

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
// Class used to transfer states of an arm's joint drivers
// Uses talky language.
class DataBlockJointDrivers : public talky::DataBlock
{    
   private:
        static log4cxx::LoggerPtr logger;
        // arm joint driver states
        int stateHS;    
        int stateVS;    
        int stateEL;    
        int stateHW;    
        int stateVW;    

    public:
        DataBlockJointDrivers();
        ~DataBlockJointDrivers();
        
        // reset all values
        void resetData();        
        // set state values for each joint driver
        void setStateHS(int value) {stateHS = value;}
        void setStateVS(int value) {stateVS = value;}
        void setStateEL(int value) {stateEL = value;}
        void setStateHW(int value) {stateHW = value;}
        void setStateVW(int value) {stateVW = value;}        
        // gets state values from each joint driver
        int getStateHS() {return stateHS;};        
        int getStateVS() {return stateVS;};        
        int getStateEL() {return stateEL;};        
        int getStateHW() {return stateHW;};        
        int getStateVW() {return stateVW;};                

        // check if specified object has same values
        bool isEqual(DataBlockJointDrivers& oArmJointInfo);

        // reads joint stateitions from given command block
        bool readBlock(talky::CommandBlock& oCommandBlock);
        // writes joint stateitions to given command block
        bool writeBlock(talky::CommandBlock& oCommandBlock);
        
        // returns a description of the object
        virtual std::string toString();        
};

}    
#endif

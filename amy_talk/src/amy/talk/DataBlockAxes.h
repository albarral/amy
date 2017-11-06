#ifndef __AMY_TALK_DATABLOCKAXES_H
#define __AMY_TALK_DATABLOCKAXES_H

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
// Class used to transfer data of an arm's axes
// Uses talky language.
class DataBlockAxes : public talky::DataBlock
{    
   private:
        static log4cxx::LoggerPtr logger;
        // arm axes positions
        float pan;    
        float tilt;    
        float radius;    
        // arm axes speeds
        float panSpeed;    
        float tiltSpeed;    

    public:
        DataBlockAxes();
        ~DataBlockAxes();
        
        // reset all values
        void resetData();        
        // set pos values for each joint
        void setPan(float value) {pan = value;}
        void setTilt(float value) {tilt = value;}
        void setRadius(float value) {radius = value;}
        void setPanSpeed(float value) {panSpeed = value;}
        void setTiltSpeed(float value) {tiltSpeed = value;}        
        // gets pos values from each joints
        float getPan() {return pan;};        
        float getTilt() {return tilt;};        
        float getRadius() {return radius;};        
        float getPanSpeed() {return panSpeed;};        
        float getTiltSpeed() {return tiltSpeed;};                

        // check if specified object has same values
        bool isEqual(DataBlockAxes& oArmJointInfo);

        // reads joint positions from given command block
        bool readBlock(talky::CommandBlock& oCommandBlock);
        // writes joint positions to given command block
        bool writeBlock(talky::CommandBlock& oCommandBlock);
        
        // returns a description of the object
        virtual std::string toString();        
};

}    
#endif

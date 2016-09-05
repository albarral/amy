#ifndef __AMY_JOINT_MOVER_H
#define __AMY_JOINT_MOVER_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "amy/utils/module2.h"
#include "amy/utils/Click.h"
#include "amy/arm/config/ParamsJointMover.h"
#include "amy/arm/bus/JointBus.h"

namespace amy
{
// Module designed to perform dynamic, but soft movements with a joint.     
// Each movements has 2 stages: an acceleration one and a cruise one (when the cruise speed is reached). 
// These 2 stages provide fast movements with limited accelerations, thus granting speed continuity (without abrupt changes) and high dynamism.
// The module is controlled with 4 simple commands (accel, brake, keep & stop) and the desired cruise speed.
// It works with 4 states:
// STOP    
// move() -> ACCEL    (speed ++)
// brake() -> BRAKE     (speed --)
// keep() -> KEEP        (speed =) 
// stop()-> STOP         (speed 0)
class JointMover : public Module2
{
public:
    // aliases for JMover commands
    static const std::string mov_positive;
    static const std::string mov_negative;
    static const std::string move_brake;
    static const std::string move_keep;
    static const std::string move_stop;

    // input commands
    enum eCommands
    {
        eMOV_POSITIVE,
        eMOV_NEGATIVE,
        eMOV_BRAKE,
        eMOV_KEEP,
        eMOV_STOP
    };

    // states of JointMover module
    enum eType
    {
         eSTATE_ACCEL,      // controls the joint speed to do the required movement
         eSTATE_BRAKE,      // brakes the joint softly
         eSTATE_KEEP,        // keeps the present joint speed 
         eSTATE_STOP        // stops the joint abruptly
    };

private:
    static log4cxx::LoggerPtr logger;
    bool benabled;
    // params
    std::string modName;   // module name
    int accel;                  // acceleration/deacceleration of joint movements (degrees/s2)
    float accel_ms;             // used version of accel (degres/s)/ms
    int brakeAccel;          // deacceleration of brake movements (degrees/s2)
    float brakeAccel_ms;     // used version of brakeAccel (degres/s)/ms
    // bus
    bool bconnected;        // connected to bus
    JointBus* pJointBus;    // the bus connections corresponding to a given joint
    // control
    int direction;          // direction of movement (positive or negative)
    float cruiseSpeed;  // cruise speed of the movement, always positive (degrees/s)
    // logic
    float targetSpeed;  // speed target to be achieved in each movement (direction * cruise_speed)    
    float sollSpeed;      // final speed commanded to output (degrees/s) (is always continuous)
    amy::Click oClick;   
    // aux
    float lastOutput;

public:
        JointMover();
        //~JointMover();
                
       // module params
       void init (std::string jointName, ParamsJointMover& oParamsJointMover);       
       bool isEnabled() {return benabled;};

       // bus connection 
       void connect(JointBus& oConnectionsJoint);
       bool isConnected() {return bconnected;};
       // params
        void setAccel(int value) {accel = value;};
        void setBrakeAccel(int value) {brakeAccel = value;};
        int getAccel() {return accel;};
        int getBrakeAccel() {return brakeAccel;};                
        // control
        int getDirection() {return direction;};        
        int getCruiseSpeed() {return cruiseSpeed;};
        // logic
        float getOutputSpeed() {return sollSpeed;};
        
        static std::string getAlias4Command(int command);
        
private:       
        // first actions when the thread begins 
        virtual void first();
        // loop inside the module thread 
        virtual void loop();            
        
        // read bus data
        void senseBus();
        // write data to bus (speed)
        void writeBus();

        // process action requests (from bus)
        void actionRequest(int value);
        // process speed requests (from bus)
        void speedRequest(float value);
        // updates the target speed
        void changeTargetSpeed();
        
        // softly changes the output speed to achieve the target value
        bool accelMovement();
        // softly reduces speed to 0
        void brakeMovement();
                
        // shows the present state name
        void showState();
};
}
#endif

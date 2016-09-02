#ifndef __AMY_MOVE_STEP_H
#define __AMY_MOVE_STEP_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


namespace amy
{
// Class that represents a 2D move step, the basic unit by which arm movements are composed.
// It involves:
// - a 2D direction -> given by an angle in the frontal plane
// - a 2D speed (reached after acceleration) 
// - a given duration (in tics)
// Creation: only the angle, duration and maxSpeed need to be specified.
// Computation (required): the proper cruise speeds and JointMover commands for each joint need to be calculated (see ArmComputer class).
    
class MoveStep
{
private:
    bool bcomputed; // indicates cruise speeds & move commands are computed
    // params
    int angle;   // movement direction in frontal xy plane (degrees)
    int tics;      // movement duration (in tics)
    int vmax;   // max speed allowed for all joint
    // logic
    int xmove;     // JointMover commands for horizontal movement 
    int ymove;     // JointMover commands for vertical movement
    float vx;  // cruise speed for horizontal movement 
    float vy;  // cruise speed for vertical movement 

public:    
    MoveStep();
    MoveStep(int angle, int tics, int maxSpeed);
//    ~MoveStep();

    void setComputed(bool value) {bcomputed = value;};
    bool isComputed() {return bcomputed;}
    
    void setAngle(int value) {angle = value;};
    void setTics(int value) {tics = value;};
    void setMaxSpeed(int value) {vmax = value;};    
    
    int getAngle() {return angle;}
    int getTics() {return tics;}
    int getMaxSpeed() {return vmax;}
    
    int setXmove(int value) {xmove = value;}
    int setYmove(int value) {ymove = value;}
    int setXspeed(float value) {vx = value;}
    int setYspeed(float value) {vy = value;}

    int getXmove() {return xmove;}
    int getYmove() {return ymove;}
    int getXspeed() {return vx;}
    int getYspeed() {return vy;}
    
    virtual bool is3D() {return false;};
};
}
#endif

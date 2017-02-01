#ifndef __AMY_CORE_MOVESTATE_H
#define __AMY_CORE_MOVESTATE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


namespace amy
{
// Class to represent the state of a move. 
class MoveState
{
private:
    // move state
    enum eType
    {
         eMOVE_DONE,                // the move is done
         eMOVE_REQUESTED,       // new move requested   
         eMOVE_GOING,               // the move is being done
         eMOVE_BLOCKED            // the move is blocked
    };
    bool bnewMove;          
    bool bmoveBlocked;    
    bool bmoveDone;        

    int state;
   
public:    
    MoveState();
    //~MoveState();

    void moveRequested();
    void moveGoing();
    void moveBlocked();
    void moveDone();
    
    bool isRequested() {return (state == eMOVE_REQUESTED);}
    bool isGoing() {return (state == eMOVE_GOING);}
    bool isBlocked() {return (state == eMOVE_BLOCKED);}
    bool isDone() {return (state == eMOVE_DONE);}        
};
}
#endif

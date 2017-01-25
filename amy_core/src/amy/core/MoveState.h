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
         eMOVE_DONE,        // the move is done
         eMOVE_NEW,          // new move requested   
         eMOVE_DOING,       // the move is being done
         eMOVE_BLOCKED    // the move is blocked
    };
    bool bnewMove;          
    bool bmoveBlocked;    
    bool bmoveDone;        

    int state;
   
public:    
    MoveState();
    //~MoveState();

    void moveRequested();
    void moveDoing();
    void moveBlocked();
    void moveDone();
    
    bool isNew() {return (state == eMOVE_NEW);}
    bool isDoing() {return (state == eMOVE_DOING);}
    bool isBlocked() {return (state == eMOVE_BLOCKED);}
    bool isDone() {return (state == eMOVE_DONE);}        
};
}
#endif

#ifndef __AMY_MOVE_CYCLICMOVE_H
#define __AMY_MOVE_CYCLICMOVE_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

namespace amy
{
// Class used to compute cyclic linear movements.
class CyclicMove
{
public:
    //CyclicMove();
    //~CyclicMove();                

    static float getTriangularSpeed4Movement(float freq, float amp);
};
}
#endif

#ifndef __AMY_SHOW_PLOT_H
#define __AMY_SHOW_PLOT_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"
#include "amy/utils/Record.h"

namespace amy 
{
// This class plots a record in a window and shows it.
class Plot
{          
public:
    //Plot();       

    // plots the given record in a window
    static void plotRecord(Record& oRecord);
};
}    
#endif

#ifndef __AMY_COMS_COMSDATA_H
#define __AMY_COMS_COMSDATA_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include <vector>

namespace amy
{    
// Class used to share coms data. Thread safe.
class ComsData
{
public:
    // special actions
    enum eAction
    {
         eACTION_AMY_END,            // end amy process
         eACTION_SHOW_GUI,          // show gui
         eACTION_HIDE_GUI             // hide gui
    };
    
private:    
    std::mutex mutex;
    std::vector<int> listSpecialActions;
    
public:
  ComsData();
  ~ComsData();
  
  // returns copy of actions list
  std::vector<int> getListSpecialActions();
  // checks if there are actions in the list
  bool hasPendingActions();
  void addSpecialAction(int action);
  void reset();  
  
};
}		

#endif

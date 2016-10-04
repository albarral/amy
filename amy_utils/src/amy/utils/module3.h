#ifndef __AMY_UTILS_MODULE3_H
#define __AMY_UTILS_MODULE3_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <thread>
#include <mutex>

namespace amy
{
// Base class designed to run a module inside its own thread.
// The loop() method must be implemented in the derived class: .    
// Methods to start & stop the module:
// - on() -> starts the module.
// - off()  -> asks the module to stop.
// - wait() -> waits till the thread is finished.
// Thread safety implemented.    
class Module3 
{
private:
        std::mutex mutex;
        std::thread t;        // module's thread       
        int state;             // module's present state
        int prevState;       // module's next state
        float frequency;    // 
        int period;           // time (microseconds) to be slept between loop executions
        bool boffRequested;    // indicates off has been requested
        static const int state_OFF = 99;
        static const int state_UNKNOWN = 100;

public:
        Module3();
        //~Module3();
                
        // starts the thread
        void on();                
        // asks the thread to stop
        void off();        
        // waits till the thread is finished
        void wait();
        
        // sets the desired loop frequency 
        void setFrequency(float cps);
        // gets the loop frequency 
        float getFrequency();

        // checks the module state
        int getState();
        // checks the module previous state
        int getPrevState();
        
protected:
        // method running inside the thread 
        void run();
        // checks if off was requested
        bool offRequested();     
        
        // first actions when the thread begins 
        virtual void first() = 0;
        // loops inside the thread 
        virtual void loop() = 0;            
        
        // sets a new state (ignore it if in OFF state)
        void setState(int state);
        // cheks if state has changed
        bool isStateChanged();
        
private:        
        // stores previous state
        void storePrevState();
};
}    
#endif

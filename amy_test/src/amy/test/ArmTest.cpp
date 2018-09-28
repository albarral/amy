/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>

#include "amy/test/ArmTest.h"
#include "amy/interface2/control/JointsClient.h"
#include "amy/interface2/control/AxesClient.h"
#include "amy/interface2/control/CyclerClient.h"
#include "amy/arm/move/JointDrive.h"
#include "amy/arm/move/JointControl.h"
#include "amy/arm/move/RadialControl.h"

using namespace log4cxx;

namespace amy
{
LoggerPtr ArmTest::logger(Logger::getLogger("amy"));    

ArmTest::ArmTest()
{
}

void ArmTest::testJointPos()
{
    LOG4CXX_INFO(logger, "testJointPos");
    
    JointsClient oJointsClient;        
    // time needed for publisher to prepare (2s)
    usleep(2000000);            

    oJointsClient.setHS(10.0);
    oJointsClient.setVS(15.0);
    oJointsClient.setELB(20.0);
    
    // time needed for publisher to stay alive (500ms))
    usleep(500000);            
}

void ArmTest::testAxesPos(int pan, int tilt, int radius)
{
    LOG4CXX_INFO(logger, "testAxesPos: " << pan << ", " << tilt << ", " << radius);

    AxesClient oAxesClient;    
    // time needed for publisher to prepare (2s)
    usleep(2000000);            

    oAxesClient.setPan(pan);
    oAxesClient.setTilt(tilt);
    oAxesClient.setRadial(radius);

    usleep(1000000);    
}

void ArmTest::testAxesSpeed(int vpan, int vtilt, int vradius)
{
    AxesClient oAxesClient;    
    // time needed for publisher to prepare (2s)
    usleep(2000000);            

    oAxesClient.setPanSpeed(vpan);
    oAxesClient.setTiltSpeed(vtilt);
    oAxesClient.setRadialSpeed(vradius);

    // wait 5s
    usleep(5000000);        

    //stop movement
    oAxesClient.setPanSpeed(0);
    oAxesClient.setTiltSpeed(0);
    oAxesClient.setRadialSpeed(0);

    usleep(1000000);    
}

void ArmTest::testCycler()
{
    LOG4CXX_INFO(logger, "testCycler");    
            
    float amplitude = 40;
    float angle = 0; 
    float angle2 = angle + 90; 
    float freq = 0.3;
    int phase = 0;
    int phase2 = phase + 90;
    
    CyclerClient oCyclerClient;
    oCyclerClient.tune2Cycler(1);
     // time needed for publisher to prepare (2s)
    usleep(2000000);            
   
    if (oCyclerClient.isTuned())
    {
        // cycler main component        
        oCyclerClient.setMainAmplitude(amplitude);
        oCyclerClient.setMainAngle(angle);
        oCyclerClient.setMainFreq(freq);
        oCyclerClient.setMainPhase(phase);            

        // cycler secondary component
        oCyclerClient.setSecondaryAmplitude(amplitude);
        oCyclerClient.setSecondaryAngle(angle2);
        oCyclerClient.setSecondaryFreq(freq);
        oCyclerClient.setSecondaryPhase(phase2);                    
        
        // move for 5 seconds and stop
        oCyclerClient.run(true);        
        sleep(10);
        oCyclerClient.run(false);               
    }
}


void ArmTest::testJointAccelerator()
{
    JointDrive oMover;
  
    LOG4CXX_INFO(logger, "\nNew test JointMove ...\n");
    
    float accel = 10.0;
    float angle = oMover.getAngle();
    for (int i=0; i<5; i++)
    {
        angle = oMover.getAngle();
        accel += 10;
        oMover.move(accel, angle);
        LOG4CXX_INFO(logger, oMover.toString() << "\n");
        sleep(1);
    }    
}

void ArmTest::testJointPositioner()
{
    JointDrive oMover;
    JointControl oDriver;
    float angle, accel;
  
    LOG4CXX_INFO(logger, "\nNew test JointControl ...\n");
    
    oDriver.init(4.0, 2.0, 0.05, 60.0);
    
    oDriver.newMove(180.0);    
    while (oDriver.getState() != JointControl::eSTATE_DONE)
    {
        angle = oMover.getAngle();
        accel = oDriver.drive(angle);
        oMover.move(accel, angle);
        LOG4CXX_INFO(logger, oDriver.toString() << "\n");
        LOG4CXX_INFO(logger, oMover.toString() << "\n");
        usleep(100000);
    }    
}

void ArmTest::testRadialPositioner()
{
    JointDrive oMover;
    RadialControl oDriver;
    float angle, accel;
  
    LOG4CXX_INFO(logger, "\nNew test RadialControl ...\n");
    
    oDriver.init(4.0, 2.0, 0.05, 60.0);
    oDriver.setArmSize(40, 40);
    
    oDriver.newRadialMove(40);
    while (oDriver.getState() != JointControl::eSTATE_DONE)
    {
        angle = oMover.getAngle();
        accel = oDriver.drive(angle);
        oMover.move(accel, angle);
        LOG4CXX_INFO(logger, oDriver.toString() << "\n");
        LOG4CXX_INFO(logger, oMover.toString() << "\n");
        usleep(100000);
    }    
}

}
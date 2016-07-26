# amy

amy is a family of C++ libraries (linux) oriented to robotic arm manipulation. 

It is aimed at offering a simple and natural approach to manipulation tasks. 

Our arm movements are not based in strict position control strategy where:
- the arm trajectory needs to be precomputed for each movement
- the joints are driven by a stric sequence of position waypoints

Instead, our movements are based in a simpler and more dynamical speed control strategy where:
- there's no predefined trajectory to be followed
- the joints are simply driven by acceleration and deceleration commands

The amy package is composed by:
- arm executable
- amy_utils library (libamy_utils)

And has the following dependencies:
- log4cxx (logging library)

IDE: Netbeans 8.1

Developmental stage: beta


JL Albarral
albarral@migtron.com


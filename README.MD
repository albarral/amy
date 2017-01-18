# amy

amy is a family of C++ libraries (linux) oriented to robotic arm manipulation. 

It's been designed to offer a very simple and natural approach to manipulation tasks. 

Amy doesn't rely on a typical position control strategy to generate arm movements. A speed control strategy is used instead.

This way we avoid:
- needing to compute the whole arm trajectory before each movement

Simpler and more dynamical movements are achieved: 
- by simply driving the joints through acceleration and deceleration commands

The amy package is composed by an executable:
- the amy program (able to control 1 or 2 arms)

And a set of auxiliary libs that provide functionalities such as movement generation or inteprocess communications:
- libamy_core.so
- libamy_utils.so
- libamy_arm.so
- libamy_coms.so

The package has the following dependencies:
- log4cxx (for powerful logging)


And it's been developed with a Netbeans 8.1 IDE.

Stage: in development

Originally created by Jose Luis Albarral
albarral@migtron.com


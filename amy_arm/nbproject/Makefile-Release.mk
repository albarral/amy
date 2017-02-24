#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/amy/arm/ArmInterface.o \
	${OBJECTDIR}/src/amy/arm/ArmManager.o \
	${OBJECTDIR}/src/amy/arm/ArmTest.o \
	${OBJECTDIR}/src/amy/arm/bus/ArmBeat.o \
	${OBJECTDIR}/src/amy/arm/bus/ArmBus.o \
	${OBJECTDIR}/src/amy/arm/bus/JointBus.o \
	${OBJECTDIR}/src/amy/arm/config/ArmConfig.o \
	${OBJECTDIR}/src/amy/arm/data/MoveStep.o \
	${OBJECTDIR}/src/amy/arm/data/MoveStep3D.o \
	${OBJECTDIR}/src/amy/arm/data/Movement.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmComputer.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmMover.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmPlanner.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmSense.o \
	${OBJECTDIR}/src/amy/arm/modules/AxisDriver.o \
	${OBJECTDIR}/src/amy/arm/modules/AxisRacer.o \
	${OBJECTDIR}/src/amy/arm/modules/JointDriver.o \
	${OBJECTDIR}/src/amy/arm/modules/PanDriver.o \
	${OBJECTDIR}/src/amy/arm/modules/PanRacer.o \
	${OBJECTDIR}/src/amy/arm/modules/RadialRacer.o \
	${OBJECTDIR}/src/amy/arm/modules/RadiusDriver.o \
	${OBJECTDIR}/src/amy/arm/modules/TiltDriver.o \
	${OBJECTDIR}/src/amy/arm/modules/TiltKeeper.o \
	${OBJECTDIR}/src/amy/arm/modules/TiltRacer.o \
	${OBJECTDIR}/src/amy/arm/move/ArmMath.o \
	${OBJECTDIR}/src/amy/arm/move/ArmPolarSensor.o \
	${OBJECTDIR}/src/amy/arm/move/JointAccelerator.o \
	${OBJECTDIR}/src/amy/arm/move/JointPositioner.o \
	${OBJECTDIR}/src/amy/arm/move/PIDControl.o \
	${OBJECTDIR}/src/amy/arm/move/RadialPositioner.o \
	${OBJECTDIR}/src/amy/arm/move/SpeedSensor3.o \
	${OBJECTDIR}/src/amy/arm/util/ArmModule.o \
	${OBJECTDIR}/src/amy/arm/util/ArmModule3.o \
	${OBJECTDIR}/src/amy/arm/util/JointModule.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_arm.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_arm.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_arm.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/arm/ArmInterface.o: src/amy/arm/ArmInterface.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/ArmInterface.o src/amy/arm/ArmInterface.cpp

${OBJECTDIR}/src/amy/arm/ArmManager.o: src/amy/arm/ArmManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/ArmManager.o src/amy/arm/ArmManager.cpp

${OBJECTDIR}/src/amy/arm/ArmTest.o: src/amy/arm/ArmTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/ArmTest.o src/amy/arm/ArmTest.cpp

${OBJECTDIR}/src/amy/arm/bus/ArmBeat.o: src/amy/arm/bus/ArmBeat.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/bus
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/bus/ArmBeat.o src/amy/arm/bus/ArmBeat.cpp

${OBJECTDIR}/src/amy/arm/bus/ArmBus.o: src/amy/arm/bus/ArmBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/bus
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/bus/ArmBus.o src/amy/arm/bus/ArmBus.cpp

${OBJECTDIR}/src/amy/arm/bus/JointBus.o: src/amy/arm/bus/JointBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/bus
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/bus/JointBus.o src/amy/arm/bus/JointBus.cpp

${OBJECTDIR}/src/amy/arm/config/ArmConfig.o: src/amy/arm/config/ArmConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/config
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/config/ArmConfig.o src/amy/arm/config/ArmConfig.cpp

${OBJECTDIR}/src/amy/arm/data/MoveStep.o: src/amy/arm/data/MoveStep.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/data/MoveStep.o src/amy/arm/data/MoveStep.cpp

${OBJECTDIR}/src/amy/arm/data/MoveStep3D.o: src/amy/arm/data/MoveStep3D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/data/MoveStep3D.o src/amy/arm/data/MoveStep3D.cpp

${OBJECTDIR}/src/amy/arm/data/Movement.o: src/amy/arm/data/Movement.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/data/Movement.o src/amy/arm/data/Movement.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmComputer.o: src/amy/arm/modules/ArmComputer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmComputer.o src/amy/arm/modules/ArmComputer.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmMover.o: src/amy/arm/modules/ArmMover.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmMover.o src/amy/arm/modules/ArmMover.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmPlanner.o: src/amy/arm/modules/ArmPlanner.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmPlanner.o src/amy/arm/modules/ArmPlanner.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmSense.o: src/amy/arm/modules/ArmSense.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmSense.o src/amy/arm/modules/ArmSense.cpp

${OBJECTDIR}/src/amy/arm/modules/AxisDriver.o: src/amy/arm/modules/AxisDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/AxisDriver.o src/amy/arm/modules/AxisDriver.cpp

${OBJECTDIR}/src/amy/arm/modules/AxisRacer.o: src/amy/arm/modules/AxisRacer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/AxisRacer.o src/amy/arm/modules/AxisRacer.cpp

${OBJECTDIR}/src/amy/arm/modules/JointDriver.o: src/amy/arm/modules/JointDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/JointDriver.o src/amy/arm/modules/JointDriver.cpp

${OBJECTDIR}/src/amy/arm/modules/PanDriver.o: src/amy/arm/modules/PanDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/PanDriver.o src/amy/arm/modules/PanDriver.cpp

${OBJECTDIR}/src/amy/arm/modules/PanRacer.o: src/amy/arm/modules/PanRacer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/PanRacer.o src/amy/arm/modules/PanRacer.cpp

${OBJECTDIR}/src/amy/arm/modules/RadialRacer.o: src/amy/arm/modules/RadialRacer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/RadialRacer.o src/amy/arm/modules/RadialRacer.cpp

${OBJECTDIR}/src/amy/arm/modules/RadiusDriver.o: src/amy/arm/modules/RadiusDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/RadiusDriver.o src/amy/arm/modules/RadiusDriver.cpp

${OBJECTDIR}/src/amy/arm/modules/TiltDriver.o: src/amy/arm/modules/TiltDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/TiltDriver.o src/amy/arm/modules/TiltDriver.cpp

${OBJECTDIR}/src/amy/arm/modules/TiltKeeper.o: src/amy/arm/modules/TiltKeeper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/TiltKeeper.o src/amy/arm/modules/TiltKeeper.cpp

${OBJECTDIR}/src/amy/arm/modules/TiltRacer.o: src/amy/arm/modules/TiltRacer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/TiltRacer.o src/amy/arm/modules/TiltRacer.cpp

${OBJECTDIR}/src/amy/arm/move/ArmMath.o: src/amy/arm/move/ArmMath.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/ArmMath.o src/amy/arm/move/ArmMath.cpp

${OBJECTDIR}/src/amy/arm/move/ArmPolarSensor.o: src/amy/arm/move/ArmPolarSensor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/ArmPolarSensor.o src/amy/arm/move/ArmPolarSensor.cpp

${OBJECTDIR}/src/amy/arm/move/JointAccelerator.o: src/amy/arm/move/JointAccelerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/JointAccelerator.o src/amy/arm/move/JointAccelerator.cpp

${OBJECTDIR}/src/amy/arm/move/JointPositioner.o: src/amy/arm/move/JointPositioner.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/JointPositioner.o src/amy/arm/move/JointPositioner.cpp

${OBJECTDIR}/src/amy/arm/move/PIDControl.o: src/amy/arm/move/PIDControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/PIDControl.o src/amy/arm/move/PIDControl.cpp

${OBJECTDIR}/src/amy/arm/move/RadialPositioner.o: src/amy/arm/move/RadialPositioner.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/RadialPositioner.o src/amy/arm/move/RadialPositioner.cpp

${OBJECTDIR}/src/amy/arm/move/SpeedSensor3.o: src/amy/arm/move/SpeedSensor3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/SpeedSensor3.o src/amy/arm/move/SpeedSensor3.cpp

${OBJECTDIR}/src/amy/arm/util/ArmModule.o: src/amy/arm/util/ArmModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/util/ArmModule.o src/amy/arm/util/ArmModule.cpp

${OBJECTDIR}/src/amy/arm/util/ArmModule3.o: src/amy/arm/util/ArmModule3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/util/ArmModule3.o src/amy/arm/util/ArmModule3.cpp

${OBJECTDIR}/src/amy/arm/util/JointModule.o: src/amy/arm/util/JointModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/util/JointModule.o src/amy/arm/util/JointModule.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_arm.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

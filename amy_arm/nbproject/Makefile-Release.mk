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
	${OBJECTDIR}/src/amy/arm/data/MoveStep.o \
	${OBJECTDIR}/src/amy/arm/data/MoveStep3D.o \
	${OBJECTDIR}/src/amy/arm/data/Movement.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmComputer.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmDriver.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmElbow.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmExtender.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmMover.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmPanner2.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmPlanner.o \
	${OBJECTDIR}/src/amy/arm/modules/JointControl2.o \
	${OBJECTDIR}/src/amy/arm/move/ArmMath.o \
	${OBJECTDIR}/src/amy/arm/move/JointDriver.o \
	${OBJECTDIR}/src/amy/arm/move/JointMover.o \
	${OBJECTDIR}/src/amy/arm/move/RadialDriver.o \
	${OBJECTDIR}/src/amy/arm/util/ArmMath.o \
	${OBJECTDIR}/src/amy/arm/util/ArmModule.o \
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

${OBJECTDIR}/src/amy/arm/modules/ArmDriver.o: src/amy/arm/modules/ArmDriver.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmDriver.o src/amy/arm/modules/ArmDriver.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmElbow.o: src/amy/arm/modules/ArmElbow.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmElbow.o src/amy/arm/modules/ArmElbow.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmExtender.o: src/amy/arm/modules/ArmExtender.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmExtender.o src/amy/arm/modules/ArmExtender.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmMover.o: src/amy/arm/modules/ArmMover.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmMover.o src/amy/arm/modules/ArmMover.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmPanner2.o: src/amy/arm/modules/ArmPanner2.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmPanner2.o src/amy/arm/modules/ArmPanner2.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmPlanner.o: src/amy/arm/modules/ArmPlanner.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmPlanner.o src/amy/arm/modules/ArmPlanner.cpp

${OBJECTDIR}/src/amy/arm/modules/JointControl2.o: src/amy/arm/modules/JointControl2.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/JointControl2.o src/amy/arm/modules/JointControl2.cpp

${OBJECTDIR}/src/amy/arm/move/ArmMath.o: src/amy/arm/move/ArmMath.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/ArmMath.o src/amy/arm/move/ArmMath.cpp

${OBJECTDIR}/src/amy/arm/move/JointDriver.o: src/amy/arm/move/JointDriver.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/JointDriver.o src/amy/arm/move/JointDriver.cpp

${OBJECTDIR}/src/amy/arm/move/JointMover.o: src/amy/arm/move/JointMover.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/JointMover.o src/amy/arm/move/JointMover.cpp

${OBJECTDIR}/src/amy/arm/move/RadialDriver.o: src/amy/arm/move/RadialDriver.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/RadialDriver.o src/amy/arm/move/RadialDriver.cpp

${OBJECTDIR}/src/amy/arm/util/ArmMath.o: src/amy/arm/util/ArmMath.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/util/ArmMath.o src/amy/arm/util/ArmMath.cpp

${OBJECTDIR}/src/amy/arm/util/ArmModule.o: src/amy/arm/util/ArmModule.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/util/ArmModule.o src/amy/arm/util/ArmModule.cpp

${OBJECTDIR}/src/amy/arm/util/JointModule.o: src/amy/arm/util/JointModule.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/util/JointModule.o src/amy/arm/util/JointModule.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
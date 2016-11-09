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
	${OBJECTDIR}/src/amy/arm/ArmManager.o \
	${OBJECTDIR}/src/amy/arm/Tests.o \
	${OBJECTDIR}/src/amy/arm/bus/ArmBus.o \
	${OBJECTDIR}/src/amy/arm/bus/JointBus.o \
	${OBJECTDIR}/src/amy/arm/bus/MovementControl.o \
	${OBJECTDIR}/src/amy/arm/coms/ArmCommand.o \
	${OBJECTDIR}/src/amy/arm/coms/ArmCommander.o \
	${OBJECTDIR}/src/amy/arm/coms/ArmComs1.o \
	${OBJECTDIR}/src/amy/arm/coms/ArmComsOut.o \
	${OBJECTDIR}/src/amy/arm/config/ArmConfig.o \
	${OBJECTDIR}/src/amy/arm/data/MoveStep.o \
	${OBJECTDIR}/src/amy/arm/data/MoveStep3D.o \
	${OBJECTDIR}/src/amy/arm/data/Movement.o \
	${OBJECTDIR}/src/amy/arm/main.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmComputer.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmExtender.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmMover.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmPanner2.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmPlanner.o \
	${OBJECTDIR}/src/amy/arm/modules/AxisDriver3.o \
	${OBJECTDIR}/src/amy/arm/modules/JointControl2.o \
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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arm

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arm: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arm ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/amy/arm/ArmManager.o: src/amy/arm/ArmManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/ArmManager.o src/amy/arm/ArmManager.cpp

${OBJECTDIR}/src/amy/arm/Tests.o: src/amy/arm/Tests.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/Tests.o src/amy/arm/Tests.cpp

${OBJECTDIR}/src/amy/arm/bus/ArmBus.o: src/amy/arm/bus/ArmBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/bus
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/bus/ArmBus.o src/amy/arm/bus/ArmBus.cpp

${OBJECTDIR}/src/amy/arm/bus/JointBus.o: src/amy/arm/bus/JointBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/bus
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/bus/JointBus.o src/amy/arm/bus/JointBus.cpp

${OBJECTDIR}/src/amy/arm/bus/MovementControl.o: src/amy/arm/bus/MovementControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/bus
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/bus/MovementControl.o src/amy/arm/bus/MovementControl.cpp

${OBJECTDIR}/src/amy/arm/coms/ArmCommand.o: src/amy/arm/coms/ArmCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/coms/ArmCommand.o src/amy/arm/coms/ArmCommand.cpp

${OBJECTDIR}/src/amy/arm/coms/ArmCommander.o: src/amy/arm/coms/ArmCommander.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/coms/ArmCommander.o src/amy/arm/coms/ArmCommander.cpp

${OBJECTDIR}/src/amy/arm/coms/ArmComs1.o: src/amy/arm/coms/ArmComs1.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/coms/ArmComs1.o src/amy/arm/coms/ArmComs1.cpp

${OBJECTDIR}/src/amy/arm/coms/ArmComsOut.o: src/amy/arm/coms/ArmComsOut.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/coms/ArmComsOut.o src/amy/arm/coms/ArmComsOut.cpp

${OBJECTDIR}/src/amy/arm/config/ArmConfig.o: src/amy/arm/config/ArmConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/config
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/config/ArmConfig.o src/amy/arm/config/ArmConfig.cpp

${OBJECTDIR}/src/amy/arm/data/MoveStep.o: src/amy/arm/data/MoveStep.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/data/MoveStep.o src/amy/arm/data/MoveStep.cpp

${OBJECTDIR}/src/amy/arm/data/MoveStep3D.o: src/amy/arm/data/MoveStep3D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/data/MoveStep3D.o src/amy/arm/data/MoveStep3D.cpp

${OBJECTDIR}/src/amy/arm/data/Movement.o: src/amy/arm/data/Movement.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/data/Movement.o src/amy/arm/data/Movement.cpp

${OBJECTDIR}/src/amy/arm/main.o: src/amy/arm/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/main.o src/amy/arm/main.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmComputer.o: src/amy/arm/modules/ArmComputer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmComputer.o src/amy/arm/modules/ArmComputer.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmExtender.o: src/amy/arm/modules/ArmExtender.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmExtender.o src/amy/arm/modules/ArmExtender.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmMover.o: src/amy/arm/modules/ArmMover.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmMover.o src/amy/arm/modules/ArmMover.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmPanner2.o: src/amy/arm/modules/ArmPanner2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmPanner2.o src/amy/arm/modules/ArmPanner2.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmPlanner.o: src/amy/arm/modules/ArmPlanner.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmPlanner.o src/amy/arm/modules/ArmPlanner.cpp

${OBJECTDIR}/src/amy/arm/modules/AxisDriver3.o: src/amy/arm/modules/AxisDriver3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/AxisDriver3.o src/amy/arm/modules/AxisDriver3.cpp

${OBJECTDIR}/src/amy/arm/modules/JointControl2.o: src/amy/arm/modules/JointControl2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/JointControl2.o src/amy/arm/modules/JointControl2.cpp

${OBJECTDIR}/src/amy/arm/util/ArmMath.o: src/amy/arm/util/ArmMath.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/util/ArmMath.o src/amy/arm/util/ArmMath.cpp

${OBJECTDIR}/src/amy/arm/util/ArmModule.o: src/amy/arm/util/ArmModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/util/ArmModule.o src/amy/arm/util/ArmModule.cpp

${OBJECTDIR}/src/amy/arm/util/JointModule.o: src/amy/arm/util/JointModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/util
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/util/JointModule.o src/amy/arm/util/JointModule.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arm

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

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
	${OBJECTDIR}/src/amy/arm/bus/ArmBus.o \
	${OBJECTDIR}/src/amy/arm/bus/JointBus.o \
	${OBJECTDIR}/src/amy/arm/coms/ArmCommand.o \
	${OBJECTDIR}/src/amy/arm/coms/ArmCommander.o \
	${OBJECTDIR}/src/amy/arm/coms/ArmComs1.o \
	${OBJECTDIR}/src/amy/arm/config/ArmConfig.o \
	${OBJECTDIR}/src/amy/arm/config/ParamsJoint.o \
	${OBJECTDIR}/src/amy/arm/config/ParamsJointMover.o \
	${OBJECTDIR}/src/amy/arm/data/Arm.o \
	${OBJECTDIR}/src/amy/arm/data/Joint.o \
	${OBJECTDIR}/src/amy/arm/main.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmMover.o \
	${OBJECTDIR}/src/amy/arm/modules/JointControl.o \
	${OBJECTDIR}/src/amy/arm/modules/JointMover.o


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

${OBJECTDIR}/src/amy/arm/bus/ArmBus.o: src/amy/arm/bus/ArmBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/bus
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/bus/ArmBus.o src/amy/arm/bus/ArmBus.cpp

${OBJECTDIR}/src/amy/arm/bus/JointBus.o: src/amy/arm/bus/JointBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/bus
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/bus/JointBus.o src/amy/arm/bus/JointBus.cpp

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

${OBJECTDIR}/src/amy/arm/config/ArmConfig.o: src/amy/arm/config/ArmConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/config
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/config/ArmConfig.o src/amy/arm/config/ArmConfig.cpp

${OBJECTDIR}/src/amy/arm/config/ParamsJoint.o: src/amy/arm/config/ParamsJoint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/config
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/config/ParamsJoint.o src/amy/arm/config/ParamsJoint.cpp

${OBJECTDIR}/src/amy/arm/config/ParamsJointMover.o: src/amy/arm/config/ParamsJointMover.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/config
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/config/ParamsJointMover.o src/amy/arm/config/ParamsJointMover.cpp

${OBJECTDIR}/src/amy/arm/data/Arm.o: src/amy/arm/data/Arm.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/data/Arm.o src/amy/arm/data/Arm.cpp

${OBJECTDIR}/src/amy/arm/data/Joint.o: src/amy/arm/data/Joint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/data/Joint.o src/amy/arm/data/Joint.cpp

${OBJECTDIR}/src/amy/arm/main.o: src/amy/arm/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/main.o src/amy/arm/main.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmMover.o: src/amy/arm/modules/ArmMover.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmMover.o src/amy/arm/modules/ArmMover.cpp

${OBJECTDIR}/src/amy/arm/modules/JointControl.o: src/amy/arm/modules/JointControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/JointControl.o src/amy/arm/modules/JointControl.cpp

${OBJECTDIR}/src/amy/arm/modules/JointMover.o: src/amy/arm/modules/JointMover.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/JointMover.o src/amy/arm/modules/JointMover.cpp

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

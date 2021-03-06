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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/amy/core/bus/ArmBus.o \
	${OBJECTDIR}/src/amy/core/bus/AxisBus.o \
	${OBJECTDIR}/src/amy/core/bus/CyclerBus.o \
	${OBJECTDIR}/src/amy/core/bus/JointBus.o \
	${OBJECTDIR}/src/amy/core/config/AmyConfig.o \
	${OBJECTDIR}/src/amy/core/robot/Arm.o \
	${OBJECTDIR}/src/amy/core/robot/Joint.o \
	${OBJECTDIR}/src/amy/core/robot/Robot.o


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
LDLIBSOPTIONS=-Wl,-rpath,../../tron/tron_control/dist/Debug/GNU-Linux -L../../tron/tron_control/dist/Debug/GNU-Linux -ltron_control

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_core.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_core.${CND_DLIB_EXT}: ../../tron/tron_control/dist/Debug/GNU-Linux/libtron_control.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_core.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_core.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/core/bus/ArmBus.o: src/amy/core/bus/ArmBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/core/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/tron_control/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/core/bus/ArmBus.o src/amy/core/bus/ArmBus.cpp

${OBJECTDIR}/src/amy/core/bus/AxisBus.o: src/amy/core/bus/AxisBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/core/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/tron_control/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/core/bus/AxisBus.o src/amy/core/bus/AxisBus.cpp

${OBJECTDIR}/src/amy/core/bus/CyclerBus.o: src/amy/core/bus/CyclerBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/core/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/tron_control/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/core/bus/CyclerBus.o src/amy/core/bus/CyclerBus.cpp

${OBJECTDIR}/src/amy/core/bus/JointBus.o: src/amy/core/bus/JointBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/core/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/tron_control/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/core/bus/JointBus.o src/amy/core/bus/JointBus.cpp

${OBJECTDIR}/src/amy/core/config/AmyConfig.o: src/amy/core/config/AmyConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/core/config
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/tron_control/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/core/config/AmyConfig.o src/amy/core/config/AmyConfig.cpp

${OBJECTDIR}/src/amy/core/robot/Arm.o: src/amy/core/robot/Arm.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/core/robot
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/tron_control/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/core/robot/Arm.o src/amy/core/robot/Arm.cpp

${OBJECTDIR}/src/amy/core/robot/Joint.o: src/amy/core/robot/Joint.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/core/robot
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/tron_control/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/core/robot/Joint.o src/amy/core/robot/Joint.cpp

${OBJECTDIR}/src/amy/core/robot/Robot.o: src/amy/core/robot/Robot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/core/robot
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron/tron_control/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/core/robot/Robot.o src/amy/core/robot/Robot.cpp

# Subprojects
.build-subprojects:
	cd ../../tron/tron_control && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_core.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../../tron/tron_control && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

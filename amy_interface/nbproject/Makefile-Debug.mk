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
	${OBJECTDIR}/src/amy/interface/ArmClient.o \
	${OBJECTDIR}/src/amy/interface/ArmListener.o \
	${OBJECTDIR}/src/amy/interface/ArmNode.o \
	${OBJECTDIR}/src/amy/interface/channels/ChannelSubscriber4Axes.o \
	${OBJECTDIR}/src/amy/interface/channels/ChannelSubscriber4Joints.o \
	${OBJECTDIR}/src/amy/interface/topics/AxisTopic.o \
	${OBJECTDIR}/src/amy/interface/topics/CyclicTopic.o \
	${OBJECTDIR}/src/amy/interface/topics/JointTopic.o


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
LDLIBSOPTIONS=-Wl,-rpath,../../tron2/tron2_coms/dist/Debug/GNU-Linux -L../../tron2/tron2_coms/dist/Debug/GNU-Linux -ltron2_coms -Wl,-rpath,../../tron2/tron2_robot/dist/Debug/GNU-Linux -L../../tron2/tron2_robot/dist/Debug/GNU-Linux -ltron2_robot -Wl,-rpath,../../tron/tron_wire/dist/Debug/GNU-Linux -L../../tron/tron_wire/dist/Debug/GNU-Linux -ltron_wire -Wl,-rpath,../../tron/tron_wire2/dist/Debug/GNU-Linux -L../../tron/tron_wire2/dist/Debug/GNU-Linux -ltron_wire2 -Wl,-rpath,../../tron/tron_tools/dist/Debug/GNU-Linux -L../../tron/tron_tools/dist/Debug/GNU-Linux -ltron_tools -Wl,-rpath,../../tron/tron_util/dist/Debug/GNU-Linux -L../../tron/tron_util/dist/Debug/GNU-Linux -ltron_util

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_interface.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_interface.${CND_DLIB_EXT}: ../../tron2/tron2_coms/dist/Debug/GNU-Linux/libtron2_coms.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_interface.${CND_DLIB_EXT}: ../../tron2/tron2_robot/dist/Debug/GNU-Linux/libtron2_robot.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_interface.${CND_DLIB_EXT}: ../../tron/tron_wire/dist/Debug/GNU-Linux/libtron_wire.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_interface.${CND_DLIB_EXT}: ../../tron/tron_wire2/dist/Debug/GNU-Linux/libtron_wire2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_interface.${CND_DLIB_EXT}: ../../tron/tron_tools/dist/Debug/GNU-Linux/libtron_tools.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_interface.${CND_DLIB_EXT}: ../../tron/tron_util/dist/Debug/GNU-Linux/libtron_util.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_interface.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_interface.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/interface/ArmClient.o: src/amy/interface/ArmClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface/ArmClient.o src/amy/interface/ArmClient.cpp

${OBJECTDIR}/src/amy/interface/ArmListener.o: src/amy/interface/ArmListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface/ArmListener.o src/amy/interface/ArmListener.cpp

${OBJECTDIR}/src/amy/interface/ArmNode.o: src/amy/interface/ArmNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface/ArmNode.o src/amy/interface/ArmNode.cpp

${OBJECTDIR}/src/amy/interface/channels/ChannelSubscriber4Axes.o: src/amy/interface/channels/ChannelSubscriber4Axes.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface/channels
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface/channels/ChannelSubscriber4Axes.o src/amy/interface/channels/ChannelSubscriber4Axes.cpp

${OBJECTDIR}/src/amy/interface/channels/ChannelSubscriber4Joints.o: src/amy/interface/channels/ChannelSubscriber4Joints.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface/channels
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface/channels/ChannelSubscriber4Joints.o src/amy/interface/channels/ChannelSubscriber4Joints.cpp

${OBJECTDIR}/src/amy/interface/topics/AxisTopic.o: src/amy/interface/topics/AxisTopic.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface/topics
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface/topics/AxisTopic.o src/amy/interface/topics/AxisTopic.cpp

${OBJECTDIR}/src/amy/interface/topics/CyclicTopic.o: src/amy/interface/topics/CyclicTopic.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface/topics
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface/topics/CyclicTopic.o src/amy/interface/topics/CyclicTopic.cpp

${OBJECTDIR}/src/amy/interface/topics/JointTopic.o: src/amy/interface/topics/JointTopic.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface/topics
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -I../../tron/tron_util/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface/topics/JointTopic.o src/amy/interface/topics/JointTopic.cpp

# Subprojects
.build-subprojects:
	cd ../../tron2/tron2_coms && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron2/tron2_robot && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_wire && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_wire2 && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_tools && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_util && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_interface.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../../tron2/tron2_coms && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron2/tron2_robot && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_wire && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_wire2 && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_tools && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_util && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
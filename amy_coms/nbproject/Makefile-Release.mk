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
	${OBJECTDIR}/src/amy/coms/AmyComs.o \
	${OBJECTDIR}/src/amy/coms/ArmConnector.o \
	${OBJECTDIR}/src/amy/coms/modules/ArmPublisher.o \
	${OBJECTDIR}/src/amy/coms/modules/ArmServer.o \
	${OBJECTDIR}/src/amy/coms/publisher/AxisChannelPublisher.o \
	${OBJECTDIR}/src/amy/coms/publisher/JointChannelPublisher.o \
	${OBJECTDIR}/src/amy/coms/server/CyclerChannelServer.o \
	${OBJECTDIR}/src/amy/coms/server/ExtraChannelServer.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/coms/AmyComs.o: src/amy/coms/AmyComs.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmyComs.o src/amy/coms/AmyComs.cpp

${OBJECTDIR}/src/amy/coms/ArmConnector.o: src/amy/coms/ArmConnector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/ArmConnector.o src/amy/coms/ArmConnector.cpp

${OBJECTDIR}/src/amy/coms/modules/ArmPublisher.o: src/amy/coms/modules/ArmPublisher.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/modules/ArmPublisher.o src/amy/coms/modules/ArmPublisher.cpp

${OBJECTDIR}/src/amy/coms/modules/ArmServer.o: src/amy/coms/modules/ArmServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/modules/ArmServer.o src/amy/coms/modules/ArmServer.cpp

${OBJECTDIR}/src/amy/coms/publisher/AxisChannelPublisher.o: src/amy/coms/publisher/AxisChannelPublisher.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/publisher
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/publisher/AxisChannelPublisher.o src/amy/coms/publisher/AxisChannelPublisher.cpp

${OBJECTDIR}/src/amy/coms/publisher/JointChannelPublisher.o: src/amy/coms/publisher/JointChannelPublisher.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/publisher
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/publisher/JointChannelPublisher.o src/amy/coms/publisher/JointChannelPublisher.cpp

${OBJECTDIR}/src/amy/coms/server/CyclerChannelServer.o: src/amy/coms/server/CyclerChannelServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/server
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/server/CyclerChannelServer.o src/amy/coms/server/CyclerChannelServer.cpp

${OBJECTDIR}/src/amy/coms/server/ExtraChannelServer.o: src/amy/coms/server/ExtraChannelServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/server
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/server/ExtraChannelServer.o src/amy/coms/server/ExtraChannelServer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

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
	${OBJECTDIR}/src/amy/coms/AmyClient.o \
	${OBJECTDIR}/src/amy/coms/AmyComsConfig.o \
	${OBJECTDIR}/src/amy/coms/AmyPublisher.o \
	${OBJECTDIR}/src/amy/coms/AmyServer.o \
	${OBJECTDIR}/src/amy/coms/AmySubscriber.o \
	${OBJECTDIR}/src/amy/coms/data/AmyCommand.o \
	${OBJECTDIR}/src/amy/coms/data/ArmData.o \
	${OBJECTDIR}/src/amy/coms/file/AmyFileClient.o \
	${OBJECTDIR}/src/amy/coms/file/AmyFilePublisher.o \
	${OBJECTDIR}/src/amy/coms/file/AmyFileServer.o \
	${OBJECTDIR}/src/amy/coms/file/AmyFileSubscriber.o \
	${OBJECTDIR}/src/amy/coms/zero/AmyZeroMQClient.o \
	${OBJECTDIR}/src/amy/coms/zero/AmyZeroMQPublisher.o \
	${OBJECTDIR}/src/amy/coms/zero/AmyZeroMQServer.o \
	${OBJECTDIR}/src/amy/coms/zero/AmyZeroMQSubscriber.o


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

${OBJECTDIR}/src/amy/coms/AmyClient.o: src/amy/coms/AmyClient.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmyClient.o src/amy/coms/AmyClient.cpp

${OBJECTDIR}/src/amy/coms/AmyComsConfig.o: src/amy/coms/AmyComsConfig.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmyComsConfig.o src/amy/coms/AmyComsConfig.cpp

${OBJECTDIR}/src/amy/coms/AmyPublisher.o: src/amy/coms/AmyPublisher.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmyPublisher.o src/amy/coms/AmyPublisher.cpp

${OBJECTDIR}/src/amy/coms/AmyServer.o: src/amy/coms/AmyServer.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmyServer.o src/amy/coms/AmyServer.cpp

${OBJECTDIR}/src/amy/coms/AmySubscriber.o: src/amy/coms/AmySubscriber.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmySubscriber.o src/amy/coms/AmySubscriber.cpp

${OBJECTDIR}/src/amy/coms/data/AmyCommand.o: src/amy/coms/data/AmyCommand.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/data/AmyCommand.o src/amy/coms/data/AmyCommand.cpp

${OBJECTDIR}/src/amy/coms/data/ArmData.o: src/amy/coms/data/ArmData.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/data/ArmData.o src/amy/coms/data/ArmData.cpp

${OBJECTDIR}/src/amy/coms/file/AmyFileClient.o: src/amy/coms/file/AmyFileClient.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/file
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/file/AmyFileClient.o src/amy/coms/file/AmyFileClient.cpp

${OBJECTDIR}/src/amy/coms/file/AmyFilePublisher.o: src/amy/coms/file/AmyFilePublisher.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/file
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/file/AmyFilePublisher.o src/amy/coms/file/AmyFilePublisher.cpp

${OBJECTDIR}/src/amy/coms/file/AmyFileServer.o: src/amy/coms/file/AmyFileServer.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/file
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/file/AmyFileServer.o src/amy/coms/file/AmyFileServer.cpp

${OBJECTDIR}/src/amy/coms/file/AmyFileSubscriber.o: src/amy/coms/file/AmyFileSubscriber.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/file
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/file/AmyFileSubscriber.o src/amy/coms/file/AmyFileSubscriber.cpp

${OBJECTDIR}/src/amy/coms/zero/AmyZeroMQClient.o: src/amy/coms/zero/AmyZeroMQClient.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/zero
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/zero/AmyZeroMQClient.o src/amy/coms/zero/AmyZeroMQClient.cpp

${OBJECTDIR}/src/amy/coms/zero/AmyZeroMQPublisher.o: src/amy/coms/zero/AmyZeroMQPublisher.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/zero
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/zero/AmyZeroMQPublisher.o src/amy/coms/zero/AmyZeroMQPublisher.cpp

${OBJECTDIR}/src/amy/coms/zero/AmyZeroMQServer.o: src/amy/coms/zero/AmyZeroMQServer.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/zero
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/zero/AmyZeroMQServer.o src/amy/coms/zero/AmyZeroMQServer.cpp

${OBJECTDIR}/src/amy/coms/zero/AmyZeroMQSubscriber.o: src/amy/coms/zero/AmyZeroMQSubscriber.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/zero
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/zero/AmyZeroMQSubscriber.o src/amy/coms/zero/AmyZeroMQSubscriber.cpp

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
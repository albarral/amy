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
	${OBJECTDIR}/src/amy/main/AmyBroadcaster.o \
	${OBJECTDIR}/src/amy/main/AmyControl.o \
	${OBJECTDIR}/src/amy/main/AmyListener.o \
	${OBJECTDIR}/src/amy/main/Tests.o \
	${OBJECTDIR}/src/amy/main/main.o \
	${OBJECTDIR}/src/amy/main/robots/ArmUR5.o \
	${OBJECTDIR}/src/amy/main/robots/ArmYoubot.o \
	${OBJECTDIR}/src/amy/main/robots/SupportedRobots.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_main

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_main: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_main ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/amy/main/AmyBroadcaster.o: src/amy/main/AmyBroadcaster.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/AmyBroadcaster.o src/amy/main/AmyBroadcaster.cpp

${OBJECTDIR}/src/amy/main/AmyControl.o: src/amy/main/AmyControl.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/AmyControl.o src/amy/main/AmyControl.cpp

${OBJECTDIR}/src/amy/main/AmyListener.o: src/amy/main/AmyListener.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/AmyListener.o src/amy/main/AmyListener.cpp

${OBJECTDIR}/src/amy/main/Tests.o: src/amy/main/Tests.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/Tests.o src/amy/main/Tests.cpp

${OBJECTDIR}/src/amy/main/main.o: src/amy/main/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/main.o src/amy/main/main.cpp

${OBJECTDIR}/src/amy/main/robots/ArmUR5.o: src/amy/main/robots/ArmUR5.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/ArmUR5.o src/amy/main/robots/ArmUR5.cpp

${OBJECTDIR}/src/amy/main/robots/ArmYoubot.o: src/amy/main/robots/ArmYoubot.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/ArmYoubot.o src/amy/main/robots/ArmYoubot.cpp

${OBJECTDIR}/src/amy/main/robots/SupportedRobots.o: src/amy/main/robots/SupportedRobots.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/SupportedRobots.o src/amy/main/robots/SupportedRobots.cpp

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

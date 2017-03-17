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
	${OBJECTDIR}/src/amy/control/Click.o \
	${OBJECTDIR}/src/amy/control/Oscillator.o \
	${OBJECTDIR}/src/amy/control/PIDControl.o \
	${OBJECTDIR}/src/amy/control/brooks/control.o \
	${OBJECTDIR}/src/amy/control/brooks/inhibition.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_control.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_control.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_control.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/control/Click.o: src/amy/control/Click.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/control
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/control/Click.o src/amy/control/Click.cpp

${OBJECTDIR}/src/amy/control/Oscillator.o: src/amy/control/Oscillator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/control
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/control/Oscillator.o src/amy/control/Oscillator.cpp

${OBJECTDIR}/src/amy/control/PIDControl.o: src/amy/control/PIDControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/control
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/control/PIDControl.o src/amy/control/PIDControl.cpp

${OBJECTDIR}/src/amy/control/brooks/control.o: src/amy/control/brooks/control.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/control/brooks
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/control/brooks/control.o src/amy/control/brooks/control.cpp

${OBJECTDIR}/src/amy/control/brooks/inhibition.o: src/amy/control/brooks/inhibition.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/control/brooks
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/control/brooks/inhibition.o src/amy/control/brooks/inhibition.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_control.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
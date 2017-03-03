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
	${OBJECTDIR}/src/amy/console/AmyConnector.o \
	${OBJECTDIR}/src/amy/console/Interpreter.o \
	${OBJECTDIR}/src/amy/console/UserCommand.o \
	${OBJECTDIR}/src/amy/console/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_console

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_console: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_console ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/amy/console/AmyConnector.o: src/amy/console/AmyConnector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/console
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/console/AmyConnector.o src/amy/console/AmyConnector.cpp

${OBJECTDIR}/src/amy/console/Interpreter.o: src/amy/console/Interpreter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/console
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/console/Interpreter.o src/amy/console/Interpreter.cpp

${OBJECTDIR}/src/amy/console/UserCommand.o: src/amy/console/UserCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/console
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/console/UserCommand.o src/amy/console/UserCommand.cpp

${OBJECTDIR}/src/amy/console/main.o: src/amy/console/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/console
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/console/main.o src/amy/console/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_console

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

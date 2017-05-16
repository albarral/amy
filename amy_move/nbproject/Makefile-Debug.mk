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
	${OBJECTDIR}/src/amy/move/CyclicMove.o \
	${OBJECTDIR}/src/amy/move/LinearCycler.o \
	${OBJECTDIR}/src/amy/move/MoveFactory.o


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
LDLIBSOPTIONS=-Wl,-rpath,../amy_math/dist/Debug/GNU-Linux -L../amy_math/dist/Debug/GNU-Linux -lamy_math

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_move.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_move.${CND_DLIB_EXT}: ../amy_math/dist/Debug/GNU-Linux/libamy_math.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_move.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_move.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/move/CyclicMove.o: src/amy/move/CyclicMove.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/move
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_math/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/move/CyclicMove.o src/amy/move/CyclicMove.cpp

${OBJECTDIR}/src/amy/move/LinearCycler.o: src/amy/move/LinearCycler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/move
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_math/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/move/LinearCycler.o src/amy/move/LinearCycler.cpp

${OBJECTDIR}/src/amy/move/MoveFactory.o: src/amy/move/MoveFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/move
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_math/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/move/MoveFactory.o src/amy/move/MoveFactory.cpp

# Subprojects
.build-subprojects:
	cd ../amy_math && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_move.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../amy_math && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

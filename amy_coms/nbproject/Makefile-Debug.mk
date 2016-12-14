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
	${OBJECTDIR}/src/amy/coms/AmyClient.o \
	${OBJECTDIR}/src/amy/coms/AmyCommand.o \
	${OBJECTDIR}/src/amy/coms/file/AmyFileClient.o


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
LDLIBSOPTIONS=-Wl,-rpath,../amy_utils/dist/Debug/GNU-Linux -L../amy_utils/dist/Debug/GNU-Linux -lamy_utils

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ../amy_utils/dist/Debug/GNU-Linux/libamy_utils.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/coms/AmyClient.o: src/amy/coms/AmyClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmyClient.o src/amy/coms/AmyClient.cpp

${OBJECTDIR}/src/amy/coms/AmyCommand.o: src/amy/coms/AmyCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmyCommand.o src/amy/coms/AmyCommand.cpp

${OBJECTDIR}/src/amy/coms/file/AmyFileClient.o: src/amy/coms/file/AmyFileClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/file
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_utils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/file/AmyFileClient.o src/amy/coms/file/AmyFileClient.cpp

# Subprojects
.build-subprojects:
	cd ../amy_utils && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../amy_utils && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

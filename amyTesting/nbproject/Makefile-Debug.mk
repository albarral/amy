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
	${OBJECTDIR}/src/amy/test/AmyCommander.o \
	${OBJECTDIR}/src/amy/test/Interpreter.o \
	${OBJECTDIR}/src/amy/test/main.o


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
LDLIBSOPTIONS=-Wl,-rpath,../amy_utils/dist/Debug/GNU-Linux -L../amy_utils/dist/Debug/GNU-Linux -lamy_utils -Wl,-rpath,../amy_coms/dist/Debug/GNU-Linux -L../amy_coms/dist/Debug/GNU-Linux -lamy_coms -llog4cxx

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amytest

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amytest: ../amy_utils/dist/Debug/GNU-Linux/libamy_utils.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amytest: ../amy_coms/dist/Debug/GNU-Linux/libamy_coms.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amytest: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amytest ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/amy/test/AmyCommander.o: src/amy/test/AmyCommander.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_utils/src -I../amy_coms/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/test/AmyCommander.o src/amy/test/AmyCommander.cpp

${OBJECTDIR}/src/amy/test/Interpreter.o: src/amy/test/Interpreter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_utils/src -I../amy_coms/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/test/Interpreter.o src/amy/test/Interpreter.cpp

${OBJECTDIR}/src/amy/test/main.o: src/amy/test/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_utils/src -I../amy_coms/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/test/main.o src/amy/test/main.cpp

# Subprojects
.build-subprojects:
	cd ../amy_utils && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_coms && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amytest

# Subprojects
.clean-subprojects:
	cd ../amy_utils && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_coms && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

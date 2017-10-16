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
	${OBJECTDIR}/src/amy/coms/AmyComsServer.o \
	${OBJECTDIR}/src/amy/coms/sections/AxisServer.o \
	${OBJECTDIR}/src/amy/coms/sections/CyclicServer.o \
	${OBJECTDIR}/src/amy/coms/sections/JointServer.o \
	${OBJECTDIR}/src/amy/coms/sections/OtherServer.o


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

${OBJECTDIR}/src/amy/coms/AmyComsServer.o: src/amy/coms/AmyComsServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmyComsServer.o src/amy/coms/AmyComsServer.cpp

${OBJECTDIR}/src/amy/coms/sections/AxisServer.o: src/amy/coms/sections/AxisServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/sections
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/sections/AxisServer.o src/amy/coms/sections/AxisServer.cpp

${OBJECTDIR}/src/amy/coms/sections/CyclicServer.o: src/amy/coms/sections/CyclicServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/sections
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/sections/CyclicServer.o src/amy/coms/sections/CyclicServer.cpp

${OBJECTDIR}/src/amy/coms/sections/JointServer.o: src/amy/coms/sections/JointServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/sections
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/sections/JointServer.o src/amy/coms/sections/JointServer.cpp

${OBJECTDIR}/src/amy/coms/sections/OtherServer.o: src/amy/coms/sections/OtherServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/sections
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/sections/OtherServer.o src/amy/coms/sections/OtherServer.cpp

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

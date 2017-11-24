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
	${OBJECTDIR}/src/amy/coms/in/ComsArmControl.o \
	${OBJECTDIR}/src/amy/coms/modules/AmyBroadcaster.o \
	${OBJECTDIR}/src/amy/coms/modules/AmyListener.o \
	${OBJECTDIR}/src/amy/coms/out/ArmComsSensing.o


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

${OBJECTDIR}/src/amy/coms/in/ComsArmControl.o: src/amy/coms/in/ComsArmControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/in
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/in/ComsArmControl.o src/amy/coms/in/ComsArmControl.cpp

${OBJECTDIR}/src/amy/coms/modules/AmyBroadcaster.o: src/amy/coms/modules/AmyBroadcaster.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/modules/AmyBroadcaster.o src/amy/coms/modules/AmyBroadcaster.cpp

${OBJECTDIR}/src/amy/coms/modules/AmyListener.o: src/amy/coms/modules/AmyListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/modules/AmyListener.o src/amy/coms/modules/AmyListener.cpp

${OBJECTDIR}/src/amy/coms/out/ArmComsSensing.o: src/amy/coms/out/ArmComsSensing.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/out
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/out/ArmComsSensing.o src/amy/coms/out/ArmComsSensing.cpp

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

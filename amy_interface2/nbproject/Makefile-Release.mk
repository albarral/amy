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
	${OBJECTDIR}/src/amy/interface2/ArmNode.o \
	${OBJECTDIR}/src/amy/interface2/control/AxesClient.o \
	${OBJECTDIR}/src/amy/interface2/control/AxesServer.o \
	${OBJECTDIR}/src/amy/interface2/control/CyclerClient.o \
	${OBJECTDIR}/src/amy/interface2/control/CyclerServer.o \
	${OBJECTDIR}/src/amy/interface2/control/JointsClient.o \
	${OBJECTDIR}/src/amy/interface2/control/JointsServer.o \
	${OBJECTDIR}/src/amy/interface2/sense/AxesInformer.o \
	${OBJECTDIR}/src/amy/interface2/sense/AxesListener.o \
	${OBJECTDIR}/src/amy/interface2/sense/JointsInformer.o \
	${OBJECTDIR}/src/amy/interface2/sense/JointsListener.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_interface2.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_interface2.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_interface2.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/interface2/ArmNode.o: src/amy/interface2/ArmNode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface2
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface2/ArmNode.o src/amy/interface2/ArmNode.cpp

${OBJECTDIR}/src/amy/interface2/control/AxesClient.o: src/amy/interface2/control/AxesClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface2/control
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface2/control/AxesClient.o src/amy/interface2/control/AxesClient.cpp

${OBJECTDIR}/src/amy/interface2/control/AxesServer.o: src/amy/interface2/control/AxesServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface2/control
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface2/control/AxesServer.o src/amy/interface2/control/AxesServer.cpp

${OBJECTDIR}/src/amy/interface2/control/CyclerClient.o: src/amy/interface2/control/CyclerClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface2/control
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface2/control/CyclerClient.o src/amy/interface2/control/CyclerClient.cpp

${OBJECTDIR}/src/amy/interface2/control/CyclerServer.o: src/amy/interface2/control/CyclerServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface2/control
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface2/control/CyclerServer.o src/amy/interface2/control/CyclerServer.cpp

${OBJECTDIR}/src/amy/interface2/control/JointsClient.o: src/amy/interface2/control/JointsClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface2/control
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface2/control/JointsClient.o src/amy/interface2/control/JointsClient.cpp

${OBJECTDIR}/src/amy/interface2/control/JointsServer.o: src/amy/interface2/control/JointsServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface2/control
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface2/control/JointsServer.o src/amy/interface2/control/JointsServer.cpp

${OBJECTDIR}/src/amy/interface2/sense/AxesInformer.o: src/amy/interface2/sense/AxesInformer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface2/sense
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface2/sense/AxesInformer.o src/amy/interface2/sense/AxesInformer.cpp

${OBJECTDIR}/src/amy/interface2/sense/AxesListener.o: src/amy/interface2/sense/AxesListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface2/sense
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface2/sense/AxesListener.o src/amy/interface2/sense/AxesListener.cpp

${OBJECTDIR}/src/amy/interface2/sense/JointsInformer.o: src/amy/interface2/sense/JointsInformer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface2/sense
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface2/sense/JointsInformer.o src/amy/interface2/sense/JointsInformer.cpp

${OBJECTDIR}/src/amy/interface2/sense/JointsListener.o: src/amy/interface2/sense/JointsListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/interface2/sense
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/interface2/sense/JointsListener.o src/amy/interface2/sense/JointsListener.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_interface2.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

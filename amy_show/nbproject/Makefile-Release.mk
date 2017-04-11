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
	${OBJECTDIR}/src/amy/show/Plot.o \
	${OBJECTDIR}/src/amy/show/arm/ArmFrontView.o \
	${OBJECTDIR}/src/amy/show/arm/ArmPlot.o \
	${OBJECTDIR}/src/amy/show/arm/ArmSideView.o \
	${OBJECTDIR}/src/amy/show/history/History.o \
	${OBJECTDIR}/src/amy/show/history/History2D.o \
	${OBJECTDIR}/src/amy/show/history/HistoryPlot.o \
	${OBJECTDIR}/src/amy/show/modules/ArmPlotter.o \
	${OBJECTDIR}/src/amy/show/modules/HistoryPlotter.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/show/Plot.o: src/amy/show/Plot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/Plot.o src/amy/show/Plot.cpp

${OBJECTDIR}/src/amy/show/arm/ArmFrontView.o: src/amy/show/arm/ArmFrontView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/arm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/arm/ArmFrontView.o src/amy/show/arm/ArmFrontView.cpp

${OBJECTDIR}/src/amy/show/arm/ArmPlot.o: src/amy/show/arm/ArmPlot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/arm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/arm/ArmPlot.o src/amy/show/arm/ArmPlot.cpp

${OBJECTDIR}/src/amy/show/arm/ArmSideView.o: src/amy/show/arm/ArmSideView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/arm
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/arm/ArmSideView.o src/amy/show/arm/ArmSideView.cpp

${OBJECTDIR}/src/amy/show/history/History.o: src/amy/show/history/History.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/history
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/history/History.o src/amy/show/history/History.cpp

${OBJECTDIR}/src/amy/show/history/History2D.o: src/amy/show/history/History2D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/history
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/history/History2D.o src/amy/show/history/History2D.cpp

${OBJECTDIR}/src/amy/show/history/HistoryPlot.o: src/amy/show/history/HistoryPlot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/history
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/history/HistoryPlot.o src/amy/show/history/HistoryPlot.cpp

${OBJECTDIR}/src/amy/show/modules/ArmPlotter.o: src/amy/show/modules/ArmPlotter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/modules/ArmPlotter.o src/amy/show/modules/ArmPlotter.cpp

${OBJECTDIR}/src/amy/show/modules/HistoryPlotter.o: src/amy/show/modules/HistoryPlotter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/modules/HistoryPlotter.o src/amy/show/modules/HistoryPlotter.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

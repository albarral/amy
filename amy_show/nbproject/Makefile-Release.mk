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
	${OBJECTDIR}/src/amy/show/ArmFrontView.o \
	${OBJECTDIR}/src/amy/show/ArmPlot.o \
	${OBJECTDIR}/src/amy/show/ArmPlotter.o \
	${OBJECTDIR}/src/amy/show/ArmSideView.o \
	${OBJECTDIR}/src/amy/show/Plot.o \
	${OBJECTDIR}/src/amy/show/PlotRecord.o


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

${OBJECTDIR}/src/amy/show/ArmFrontView.o: src/amy/show/ArmFrontView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/ArmFrontView.o src/amy/show/ArmFrontView.cpp

${OBJECTDIR}/src/amy/show/ArmPlot.o: src/amy/show/ArmPlot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/ArmPlot.o src/amy/show/ArmPlot.cpp

${OBJECTDIR}/src/amy/show/ArmPlotter.o: src/amy/show/ArmPlotter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/ArmPlotter.o src/amy/show/ArmPlotter.cpp

${OBJECTDIR}/src/amy/show/ArmSideView.o: src/amy/show/ArmSideView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/ArmSideView.o src/amy/show/ArmSideView.cpp

${OBJECTDIR}/src/amy/show/Plot.o: src/amy/show/Plot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/Plot.o src/amy/show/Plot.cpp

${OBJECTDIR}/src/amy/show/PlotRecord.o: src/amy/show/PlotRecord.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/PlotRecord.o src/amy/show/PlotRecord.cpp

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

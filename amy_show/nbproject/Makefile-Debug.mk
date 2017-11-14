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
	${OBJECTDIR}/src/amy/show/AmyShow.o \
	${OBJECTDIR}/src/amy/show/ShowData.o \
	${OBJECTDIR}/src/amy/show/arm/ArmFrontView.o \
	${OBJECTDIR}/src/amy/show/arm/ArmPlot.o \
	${OBJECTDIR}/src/amy/show/arm/ArmSideView.o \
	${OBJECTDIR}/src/amy/show/modules/ShowPlotter.o \
	${OBJECTDIR}/src/amy/show/modules/ShowSenser.o \
	${OBJECTDIR}/src/amy/show/plot/ArmPlotter.o \
	${OBJECTDIR}/src/amy/show/plot/HistoryPlotter.o


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
LDLIBSOPTIONS=-Wl,-rpath,../amy_core/dist/Debug/GNU-Linux -L../amy_core/dist/Debug/GNU-Linux -lamy_core -Wl,-rpath,../../tron/tuly/dist/Debug/GNU-Linux -L../../tron/tuly/dist/Debug/GNU-Linux -ltron_tuly -Wl,-rpath,../../tron/tivy/dist/Debug/GNU-Linux -L../../tron/tivy/dist/Debug/GNU-Linux -ltron_tivy -lopencv_core -lopencv_highgui

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../amy_core/dist/Debug/GNU-Linux/libamy_core.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../../tron/tuly/dist/Debug/GNU-Linux/libtron_tuly.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../../tron/tivy/dist/Debug/GNU-Linux/libtron_tivy.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/show/AmyShow.o: src/amy/show/AmyShow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/AmyShow.o src/amy/show/AmyShow.cpp

${OBJECTDIR}/src/amy/show/ShowData.o: src/amy/show/ShowData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/ShowData.o src/amy/show/ShowData.cpp

${OBJECTDIR}/src/amy/show/arm/ArmFrontView.o: src/amy/show/arm/ArmFrontView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/arm
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/arm/ArmFrontView.o src/amy/show/arm/ArmFrontView.cpp

${OBJECTDIR}/src/amy/show/arm/ArmPlot.o: src/amy/show/arm/ArmPlot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/arm
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/arm/ArmPlot.o src/amy/show/arm/ArmPlot.cpp

${OBJECTDIR}/src/amy/show/arm/ArmSideView.o: src/amy/show/arm/ArmSideView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/arm
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/arm/ArmSideView.o src/amy/show/arm/ArmSideView.cpp

${OBJECTDIR}/src/amy/show/modules/ShowPlotter.o: src/amy/show/modules/ShowPlotter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/modules/ShowPlotter.o src/amy/show/modules/ShowPlotter.cpp

${OBJECTDIR}/src/amy/show/modules/ShowSenser.o: src/amy/show/modules/ShowSenser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/modules/ShowSenser.o src/amy/show/modules/ShowSenser.cpp

${OBJECTDIR}/src/amy/show/plot/ArmPlotter.o: src/amy/show/plot/ArmPlotter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/plot
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/plot/ArmPlotter.o src/amy/show/plot/ArmPlotter.cpp

${OBJECTDIR}/src/amy/show/plot/HistoryPlotter.o: src/amy/show/plot/HistoryPlotter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/plot
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/plot/HistoryPlotter.o src/amy/show/plot/HistoryPlotter.cpp

# Subprojects
.build-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tivy && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tivy && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

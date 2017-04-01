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
LDLIBSOPTIONS=-Wl,-rpath,'../amy_core/dist/Debug/GNU-Linux' -L../amy_core/dist/Debug/GNU-Linux -lamy_core -Wl,-rpath,'../amy_utils/dist/Debug/GNU-Linux' -L../amy_utils/dist/Debug/GNU-Linux -lamy_utils -Wl,-rpath,'../amy_control/dist/Debug/GNU-Linux' -L../amy_control/dist/Debug/GNU-Linux -lamy_control -Wl,-rpath,'../amy_arm/dist/Debug/GNU-Linux' -L../amy_arm/dist/Debug/GNU-Linux -lamy_arm -lopencv_core -lopencv_highgui

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../amy_core/dist/Debug/GNU-Linux/libamy_core.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../amy_utils/dist/Debug/GNU-Linux/libamy_utils.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../amy_control/dist/Debug/GNU-Linux/libamy_control.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../amy_arm/dist/Debug/GNU-Linux/libamy_arm.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/show/ArmFrontView.o: src/amy/show/ArmFrontView.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_utils/src -I../amy_control/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/ArmFrontView.o src/amy/show/ArmFrontView.cpp

${OBJECTDIR}/src/amy/show/ArmPlot.o: src/amy/show/ArmPlot.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_utils/src -I../amy_control/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/ArmPlot.o src/amy/show/ArmPlot.cpp

${OBJECTDIR}/src/amy/show/ArmPlotter.o: src/amy/show/ArmPlotter.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_utils/src -I../amy_control/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/ArmPlotter.o src/amy/show/ArmPlotter.cpp

${OBJECTDIR}/src/amy/show/ArmSideView.o: src/amy/show/ArmSideView.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_utils/src -I../amy_control/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/ArmSideView.o src/amy/show/ArmSideView.cpp

${OBJECTDIR}/src/amy/show/Plot.o: src/amy/show/Plot.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_utils/src -I../amy_control/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/Plot.o src/amy/show/Plot.cpp

${OBJECTDIR}/src/amy/show/PlotRecord.o: src/amy/show/PlotRecord.cpp
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_utils/src -I../amy_control/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/PlotRecord.o src/amy/show/PlotRecord.cpp

# Subprojects
.build-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_utils && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_control && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_utils.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_core.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_control.so ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_arm.so
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_utils && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_control && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

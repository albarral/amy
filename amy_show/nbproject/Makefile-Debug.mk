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
	${OBJECTDIR}/src/amy/show/DiscPlot.o \
	${OBJECTDIR}/src/amy/show/Plot.o \
	${OBJECTDIR}/src/amy/show/SharedDisplay.o \
	${OBJECTDIR}/src/amy/show/TestShow.o \
	${OBJECTDIR}/src/amy/show/arm/ArmFrontView.o \
	${OBJECTDIR}/src/amy/show/arm/ArmPlot.o \
	${OBJECTDIR}/src/amy/show/arm/ArmSideView.o \
	${OBJECTDIR}/src/amy/show/history/History.o \
	${OBJECTDIR}/src/amy/show/history/History2D.o \
	${OBJECTDIR}/src/amy/show/history/HistoryPlot.o \
	${OBJECTDIR}/src/amy/show/modules/AmyDisplayer.o \
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
LDLIBSOPTIONS=-Wl,-rpath,../amy_core/dist/Debug/GNU-Linux -L../amy_core/dist/Debug/GNU-Linux -lamy_core -Wl,-rpath,../amy_control/dist/Debug/GNU-Linux -L../amy_control/dist/Debug/GNU-Linux -lamy_control -Wl,-rpath,../amy_math/dist/Debug/GNU-Linux -L../amy_math/dist/Debug/GNU-Linux -lamy_math -Wl,-rpath,../amy_arm/dist/Debug/GNU-Linux -L../amy_arm/dist/Debug/GNU-Linux -lamy_arm -lopencv_core -lopencv_highgui

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../amy_core/dist/Debug/GNU-Linux/libamy_core.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../amy_control/dist/Debug/GNU-Linux/libamy_control.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../amy_math/dist/Debug/GNU-Linux/libamy_math.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../amy_arm/dist/Debug/GNU-Linux/libamy_arm.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/show/DiscPlot.o: src/amy/show/DiscPlot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/DiscPlot.o src/amy/show/DiscPlot.cpp

${OBJECTDIR}/src/amy/show/Plot.o: src/amy/show/Plot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/Plot.o src/amy/show/Plot.cpp

${OBJECTDIR}/src/amy/show/SharedDisplay.o: src/amy/show/SharedDisplay.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/SharedDisplay.o src/amy/show/SharedDisplay.cpp

${OBJECTDIR}/src/amy/show/TestShow.o: src/amy/show/TestShow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/TestShow.o src/amy/show/TestShow.cpp

${OBJECTDIR}/src/amy/show/arm/ArmFrontView.o: src/amy/show/arm/ArmFrontView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/arm
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/arm/ArmFrontView.o src/amy/show/arm/ArmFrontView.cpp

${OBJECTDIR}/src/amy/show/arm/ArmPlot.o: src/amy/show/arm/ArmPlot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/arm
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/arm/ArmPlot.o src/amy/show/arm/ArmPlot.cpp

${OBJECTDIR}/src/amy/show/arm/ArmSideView.o: src/amy/show/arm/ArmSideView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/arm
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/arm/ArmSideView.o src/amy/show/arm/ArmSideView.cpp

${OBJECTDIR}/src/amy/show/history/History.o: src/amy/show/history/History.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/history
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/history/History.o src/amy/show/history/History.cpp

${OBJECTDIR}/src/amy/show/history/History2D.o: src/amy/show/history/History2D.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/history
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/history/History2D.o src/amy/show/history/History2D.cpp

${OBJECTDIR}/src/amy/show/history/HistoryPlot.o: src/amy/show/history/HistoryPlot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/history
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/history/HistoryPlot.o src/amy/show/history/HistoryPlot.cpp

${OBJECTDIR}/src/amy/show/modules/AmyDisplayer.o: src/amy/show/modules/AmyDisplayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/modules/AmyDisplayer.o src/amy/show/modules/AmyDisplayer.cpp

${OBJECTDIR}/src/amy/show/modules/ArmPlotter.o: src/amy/show/modules/ArmPlotter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/modules/ArmPlotter.o src/amy/show/modules/ArmPlotter.cpp

${OBJECTDIR}/src/amy/show/modules/HistoryPlotter.o: src/amy/show/modules/HistoryPlotter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/modules/HistoryPlotter.o src/amy/show/modules/HistoryPlotter.cpp

# Subprojects
.build-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_control && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_math && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_control && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_math && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

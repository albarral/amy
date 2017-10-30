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
	${OBJECTDIR}/src/amy/show/arm/ArmFrontView.o \
	${OBJECTDIR}/src/amy/show/arm/ArmPlot.o \
	${OBJECTDIR}/src/amy/show/arm/ArmSideView.o \
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
LDLIBSOPTIONS=-Wl,-rpath,../amy_core/dist/Debug/GNU-Linux -L../amy_core/dist/Debug/GNU-Linux -lamy_core -Wl,-rpath,../amy_math/dist/Debug/GNU-Linux -L../amy_math/dist/Debug/GNU-Linux -lamy_math -Wl,-rpath,../amy_arm/dist/Debug/GNU-Linux -L../amy_arm/dist/Debug/GNU-Linux -lamy_arm -Wl,-rpath,../../tron/tuly/dist/Debug/GNU-Linux -L../../tron/tuly/dist/Debug/GNU-Linux -ltron_tuly -lopencv_core -lopencv_highgui -Wl,-rpath,../../tron/tivy/dist/Debug/GNU-Linux -L../../tron/tivy/dist/Debug/GNU-Linux -ltron_tivy

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../amy_core/dist/Debug/GNU-Linux/libamy_core.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../amy_math/dist/Debug/GNU-Linux/libamy_math.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../amy_arm/dist/Debug/GNU-Linux/libamy_arm.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../../tron/tuly/dist/Debug/GNU-Linux/libtron_tuly.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ../../tron/tivy/dist/Debug/GNU-Linux/libtron_tivy.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/show/arm/ArmFrontView.o: src/amy/show/arm/ArmFrontView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/arm
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_math/src -I../amy_arm/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/arm/ArmFrontView.o src/amy/show/arm/ArmFrontView.cpp

${OBJECTDIR}/src/amy/show/arm/ArmPlot.o: src/amy/show/arm/ArmPlot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/arm
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_math/src -I../amy_arm/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/arm/ArmPlot.o src/amy/show/arm/ArmPlot.cpp

${OBJECTDIR}/src/amy/show/arm/ArmSideView.o: src/amy/show/arm/ArmSideView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/arm
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_math/src -I../amy_arm/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/arm/ArmSideView.o src/amy/show/arm/ArmSideView.cpp

${OBJECTDIR}/src/amy/show/modules/AmyDisplayer.o: src/amy/show/modules/AmyDisplayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_math/src -I../amy_arm/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/modules/AmyDisplayer.o src/amy/show/modules/AmyDisplayer.cpp

${OBJECTDIR}/src/amy/show/modules/ArmPlotter.o: src/amy/show/modules/ArmPlotter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_math/src -I../amy_arm/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/modules/ArmPlotter.o src/amy/show/modules/ArmPlotter.cpp

${OBJECTDIR}/src/amy/show/modules/HistoryPlotter.o: src/amy/show/modules/HistoryPlotter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/show/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_math/src -I../amy_arm/src -I../../tron/tuly/src -I../../tron/tivy/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/show/modules/HistoryPlotter.o src/amy/show/modules/HistoryPlotter.cpp

# Subprojects
.build-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_math && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tivy && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_show.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_math && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tivy && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

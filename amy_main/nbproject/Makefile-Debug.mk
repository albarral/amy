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
	${OBJECTDIR}/src/amy/main/AmyBroadcaster.o \
	${OBJECTDIR}/src/amy/main/AmyControl.o \
	${OBJECTDIR}/src/amy/main/AmyListener.o \
	${OBJECTDIR}/src/amy/main/Tests.o \
	${OBJECTDIR}/src/amy/main/main.o \
	${OBJECTDIR}/src/amy/main/robots/ArmUR5.o \
	${OBJECTDIR}/src/amy/main/robots/ArmYoubot.o \
	${OBJECTDIR}/src/amy/main/robots/SupportedRobots.o


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
LDLIBSOPTIONS=-Wl,-rpath,../amy_core/dist/Debug/GNU-Linux -L../amy_core/dist/Debug/GNU-Linux -lamy_core -Wl,-rpath,../amy_utils/dist/Debug/GNU-Linux -L../amy_utils/dist/Debug/GNU-Linux -lamy_utils -Wl,-rpath,../amy_control/dist/Debug/GNU-Linux -L../amy_control/dist/Debug/GNU-Linux -lamy_control -Wl,-rpath,../amy_math/dist/Debug/GNU-Linux -L../amy_math/dist/Debug/GNU-Linux -lamy_math -Wl,-rpath,../amy_arm/dist/Debug/GNU-Linux -L../amy_arm/dist/Debug/GNU-Linux -lamy_arm -Wl,-rpath,../amy_coms/dist/Debug/GNU-Linux -L../amy_coms/dist/Debug/GNU-Linux -lamy_coms -Wl,-rpath,../amy_show/dist/Debug/GNU-Linux -L../amy_show/dist/Debug/GNU-Linux -lamy_show -llog4cxx -lopencv_core -lopencv_highgui

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_core/dist/Debug/GNU-Linux/libamy_core.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_utils/dist/Debug/GNU-Linux/libamy_utils.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_control/dist/Debug/GNU-Linux/libamy_control.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_math/dist/Debug/GNU-Linux/libamy_math.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_arm/dist/Debug/GNU-Linux/libamy_arm.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_coms/dist/Debug/GNU-Linux/libamy_coms.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_show/dist/Debug/GNU-Linux/libamy_show.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/amy/main/AmyBroadcaster.o: src/amy/main/AmyBroadcaster.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_utils/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -I../amy_coms/src -I../amy_show/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/AmyBroadcaster.o src/amy/main/AmyBroadcaster.cpp

${OBJECTDIR}/src/amy/main/AmyControl.o: src/amy/main/AmyControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_utils/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -I../amy_coms/src -I../amy_show/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/AmyControl.o src/amy/main/AmyControl.cpp

${OBJECTDIR}/src/amy/main/AmyListener.o: src/amy/main/AmyListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_utils/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -I../amy_coms/src -I../amy_show/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/AmyListener.o src/amy/main/AmyListener.cpp

${OBJECTDIR}/src/amy/main/Tests.o: src/amy/main/Tests.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_utils/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -I../amy_coms/src -I../amy_show/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/Tests.o src/amy/main/Tests.cpp

${OBJECTDIR}/src/amy/main/main.o: src/amy/main/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_utils/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -I../amy_coms/src -I../amy_show/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/main.o src/amy/main/main.cpp

${OBJECTDIR}/src/amy/main/robots/ArmUR5.o: src/amy/main/robots/ArmUR5.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_utils/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -I../amy_coms/src -I../amy_show/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/ArmUR5.o src/amy/main/robots/ArmUR5.cpp

${OBJECTDIR}/src/amy/main/robots/ArmYoubot.o: src/amy/main/robots/ArmYoubot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_utils/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -I../amy_coms/src -I../amy_show/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/ArmYoubot.o src/amy/main/robots/ArmYoubot.cpp

${OBJECTDIR}/src/amy/main/robots/SupportedRobots.o: src/amy/main/robots/SupportedRobots.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_utils/src -I../amy_control/src -I../amy_math/src -I../amy_arm/src -I../amy_coms/src -I../amy_show/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/SupportedRobots.o src/amy/main/robots/SupportedRobots.cpp

# Subprojects
.build-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_utils && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_control && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_math && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_coms && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_show && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy

# Subprojects
.clean-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_utils && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_control && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_math && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_coms && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_show && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

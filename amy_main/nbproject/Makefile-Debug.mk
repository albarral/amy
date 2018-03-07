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
	${OBJECTDIR}/src/amy/main/AmyControl.o \
	${OBJECTDIR}/src/amy/main/ArmTest.o \
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
LDLIBSOPTIONS=-Wl,-rpath,../amy_core/dist/Debug/GNU-Linux -L../amy_core/dist/Debug/GNU-Linux -lamy_core -Wl,-rpath,../amy_arm/dist/Debug/GNU-Linux -L../amy_arm/dist/Debug/GNU-Linux -lamy_arm -Wl,-rpath,../amy_coms/dist/Debug/GNU-Linux -L../amy_coms/dist/Debug/GNU-Linux -lamy_coms -Wl,-rpath,../../tron/tuly/dist/Debug/GNU-Linux -L../../tron/tuly/dist/Debug/GNU-Linux -ltron_tuly -Wl,-rpath,../../tron/maty/dist/Debug/GNU-Linux -L../../tron/maty/dist/Debug/GNU-Linux -ltron_maty -Wl,-rpath,../../tron/robot/dist/Debug/GNU-Linux -L../../tron/robot/dist/Debug/GNU-Linux -ltron_robot -Wl,-rpath,../../tron/talky2/dist/Debug/GNU-Linux -L../../tron/talky2/dist/Debug/GNU-Linux -ltron_talky2 -Wl,-rpath,../../tron/wire/dist/Debug/GNU-Linux -L../../tron/wire/dist/Debug/GNU-Linux -ltron_wire -Wl,-rpath,../../tron/wire2/dist/Debug/GNU-Linux -L../../tron/wire2/dist/Debug/GNU-Linux -ltron_wire2 -Wl,-rpath,../amy_show/dist/Debug/GNU-Linux -L../amy_show/dist/Debug/GNU-Linux -lamy_show -Wl,-rpath,../../tron/tivy/dist/Debug/GNU-Linux -L../../tron/tivy/dist/Debug/GNU-Linux -ltron_tivy -llog4cxx -lopencv_core -lopencv_highgui

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_core/dist/Debug/GNU-Linux/libamy_core.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_arm/dist/Debug/GNU-Linux/libamy_arm.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_coms/dist/Debug/GNU-Linux/libamy_coms.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/tuly/dist/Debug/GNU-Linux/libtron_tuly.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/maty/dist/Debug/GNU-Linux/libtron_maty.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/robot/dist/Debug/GNU-Linux/libtron_robot.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/talky2/dist/Debug/GNU-Linux/libtron_talky2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/wire/dist/Debug/GNU-Linux/libtron_wire.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/wire2/dist/Debug/GNU-Linux/libtron_wire2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_show/dist/Debug/GNU-Linux/libamy_show.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/tivy/dist/Debug/GNU-Linux/libtron_tivy.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/amy/main/AmyControl.o: src/amy/main/AmyControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_arm/src -I../amy_coms/src -I../../tron/tuly/src -I../../tron/maty/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -I../amy_show/src -I../../tron/tivy/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/AmyControl.o src/amy/main/AmyControl.cpp

${OBJECTDIR}/src/amy/main/ArmTest.o: src/amy/main/ArmTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_arm/src -I../amy_coms/src -I../../tron/tuly/src -I../../tron/maty/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -I../amy_show/src -I../../tron/tivy/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/ArmTest.o src/amy/main/ArmTest.cpp

${OBJECTDIR}/src/amy/main/main.o: src/amy/main/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_arm/src -I../amy_coms/src -I../../tron/tuly/src -I../../tron/maty/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -I../amy_show/src -I../../tron/tivy/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/main.o src/amy/main/main.cpp

${OBJECTDIR}/src/amy/main/robots/ArmUR5.o: src/amy/main/robots/ArmUR5.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_arm/src -I../amy_coms/src -I../../tron/tuly/src -I../../tron/maty/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -I../amy_show/src -I../../tron/tivy/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/ArmUR5.o src/amy/main/robots/ArmUR5.cpp

${OBJECTDIR}/src/amy/main/robots/ArmYoubot.o: src/amy/main/robots/ArmYoubot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_arm/src -I../amy_coms/src -I../../tron/tuly/src -I../../tron/maty/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -I../amy_show/src -I../../tron/tivy/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/ArmYoubot.o src/amy/main/robots/ArmYoubot.cpp

${OBJECTDIR}/src/amy/main/robots/SupportedRobots.o: src/amy/main/robots/SupportedRobots.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_arm/src -I../amy_coms/src -I../../tron/tuly/src -I../../tron/maty/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -I../amy_show/src -I../../tron/tivy/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/SupportedRobots.o src/amy/main/robots/SupportedRobots.cpp

# Subprojects
.build-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_coms && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/robot && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/talky2 && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/wire && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/wire2 && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_show && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tivy && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy

# Subprojects
.clean-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_coms && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/robot && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/talky2 && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/wire && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/wire2 && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_show && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tivy && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

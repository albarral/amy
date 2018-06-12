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
LDLIBSOPTIONS=-Wl,-rpath,../amy_core/dist/Debug/GNU-Linux -L../amy_core/dist/Debug/GNU-Linux -lamy_core -Wl,-rpath,../amy_arm/dist/Debug/GNU-Linux -L../amy_arm/dist/Debug/GNU-Linux -lamy_arm -Wl,-rpath,../amy_coms/dist/Debug/GNU-Linux -L../amy_coms/dist/Debug/GNU-Linux -lamy_coms -Wl,-rpath,../amy_interface/dist/Debug/GNU-Linux -L../amy_interface/dist/Debug/GNU-Linux -lamy_interface -Wl,-rpath,../amy_show/dist/Debug/GNU-Linux -L../amy_show/dist/Debug/GNU-Linux -lamy_show -Wl,-rpath,../../tron2/tron2_coms/dist/Debug/GNU-Linux -L../../tron2/tron2_coms/dist/Debug/GNU-Linux -ltron2_coms -Wl,-rpath,../../tron2/tron2_robot/dist/Debug/GNU-Linux -L../../tron2/tron2_robot/dist/Debug/GNU-Linux -ltron2_robot -Wl,-rpath,../../tron2/tron2_tivy/dist/Debug/GNU-Linux -L../../tron2/tron2_tivy/dist/Debug/GNU-Linux -ltron2_tivy -Wl,-rpath,../../tron/tron_control/dist/Debug/GNU-Linux -L../../tron/tron_control/dist/Debug/GNU-Linux -ltron_control -Wl,-rpath,../../tron/tron_math/dist/Debug/GNU-Linux -L../../tron/tron_math/dist/Debug/GNU-Linux -ltron_math -Wl,-rpath,../../tron/tron_signals/dist/Debug/GNU-Linux -L../../tron/tron_signals/dist/Debug/GNU-Linux -ltron_signals -Wl,-rpath,../../tron/tron_tools/dist/Debug/GNU-Linux -L../../tron/tron_tools/dist/Debug/GNU-Linux -ltron_tools -Wl,-rpath,../../tron/tron_util/dist/Debug/GNU-Linux -L../../tron/tron_util/dist/Debug/GNU-Linux -ltron_util -Wl,-rpath,../../tron/tron_wire/dist/Debug/GNU-Linux -L../../tron/tron_wire/dist/Debug/GNU-Linux -ltron_wire -Wl,-rpath,../../tron/tron_wire2/dist/Debug/GNU-Linux -L../../tron/tron_wire2/dist/Debug/GNU-Linux -ltron_wire2 -llog4cxx -lopencv_core -lopencv_highgui

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_core/dist/Debug/GNU-Linux/libamy_core.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_arm/dist/Debug/GNU-Linux/libamy_arm.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_coms/dist/Debug/GNU-Linux/libamy_coms.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_interface/dist/Debug/GNU-Linux/libamy_interface.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_show/dist/Debug/GNU-Linux/libamy_show.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron2/tron2_coms/dist/Debug/GNU-Linux/libtron2_coms.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron2/tron2_robot/dist/Debug/GNU-Linux/libtron2_robot.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron2/tron2_tivy/dist/Debug/GNU-Linux/libtron2_tivy.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/tron_control/dist/Debug/GNU-Linux/libtron_control.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/tron_math/dist/Debug/GNU-Linux/libtron_math.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/tron_signals/dist/Debug/GNU-Linux/libtron_signals.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/tron_tools/dist/Debug/GNU-Linux/libtron_tools.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/tron_util/dist/Debug/GNU-Linux/libtron_util.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/tron_wire/dist/Debug/GNU-Linux/libtron_wire.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/tron_wire2/dist/Debug/GNU-Linux/libtron_wire2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/amy/main/AmyControl.o: src/amy/main/AmyControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_arm/src -I../amy_coms/src -I../amy_interface/src -I../amy_show/src -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron2/tron2_tivy/src -I../../tron/tron_control/src -I../../tron/tron_math/src -I../../tron/tron_signals/src -I../../tron/tron_util/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/AmyControl.o src/amy/main/AmyControl.cpp

${OBJECTDIR}/src/amy/main/ArmTest.o: src/amy/main/ArmTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_arm/src -I../amy_coms/src -I../amy_interface/src -I../amy_show/src -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron2/tron2_tivy/src -I../../tron/tron_control/src -I../../tron/tron_math/src -I../../tron/tron_signals/src -I../../tron/tron_util/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/ArmTest.o src/amy/main/ArmTest.cpp

${OBJECTDIR}/src/amy/main/main.o: src/amy/main/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_arm/src -I../amy_coms/src -I../amy_interface/src -I../amy_show/src -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron2/tron2_tivy/src -I../../tron/tron_control/src -I../../tron/tron_math/src -I../../tron/tron_signals/src -I../../tron/tron_util/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/main.o src/amy/main/main.cpp

${OBJECTDIR}/src/amy/main/robots/ArmUR5.o: src/amy/main/robots/ArmUR5.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_arm/src -I../amy_coms/src -I../amy_interface/src -I../amy_show/src -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron2/tron2_tivy/src -I../../tron/tron_control/src -I../../tron/tron_math/src -I../../tron/tron_signals/src -I../../tron/tron_util/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/ArmUR5.o src/amy/main/robots/ArmUR5.cpp

${OBJECTDIR}/src/amy/main/robots/ArmYoubot.o: src/amy/main/robots/ArmYoubot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_arm/src -I../amy_coms/src -I../amy_interface/src -I../amy_show/src -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron2/tron2_tivy/src -I../../tron/tron_control/src -I../../tron/tron_math/src -I../../tron/tron_signals/src -I../../tron/tron_util/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/ArmYoubot.o src/amy/main/robots/ArmYoubot.cpp

${OBJECTDIR}/src/amy/main/robots/SupportedRobots.o: src/amy/main/robots/SupportedRobots.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_arm/src -I../amy_coms/src -I../amy_interface/src -I../amy_show/src -I../../tron2/tron2_coms/src -I../../tron2/tron2_robot/src -I../../tron2/tron2_tivy/src -I../../tron/tron_control/src -I../../tron/tron_math/src -I../../tron/tron_signals/src -I../../tron/tron_util/src -I../../tron/tron_wire/src -I../../tron/tron_wire2/src -I../../tron/tron_tools/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/SupportedRobots.o src/amy/main/robots/SupportedRobots.cpp

# Subprojects
.build-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_coms && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_interface && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_show && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron2/tron2_coms && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron2/tron2_robot && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron2/tron2_tivy && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_control && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_math && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_signals && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_tools && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_util && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_wire && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_wire2 && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy

# Subprojects
.clean-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_coms && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_interface && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_show && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron2/tron2_coms && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron2/tron2_robot && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron2/tron2_tivy && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_control && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_math && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_signals && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_tools && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_util && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_wire && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_wire2 && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

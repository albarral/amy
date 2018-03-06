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
	${OBJECTDIR}/src/amy/coms/AmyComs.o \
	${OBJECTDIR}/src/amy/coms/ArmConnector.o \
	${OBJECTDIR}/src/amy/coms/in/ComsInArmControl.o \
	${OBJECTDIR}/src/amy/coms/modules/AmyBroadcaster.o \
	${OBJECTDIR}/src/amy/coms/modules/AmyListener.o \
	${OBJECTDIR}/src/amy/coms/out/ComsOutArmSense.o \
	${OBJECTDIR}/src/amy/coms/server/ArmServer.o \
	${OBJECTDIR}/src/amy/coms/server/AxisChannelServer.o \
	${OBJECTDIR}/src/amy/coms/server/CyclicChannelServer.o \
	${OBJECTDIR}/src/amy/coms/server/ExtraChannelServer.o \
	${OBJECTDIR}/src/amy/coms/server/JointChannelServer.o


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
LDLIBSOPTIONS=-Wl,-rpath,../amy_core/dist/Debug/GNU-Linux -L../amy_core/dist/Debug/GNU-Linux -lamy_core -Wl,-rpath,../amy_talk/dist/Debug/GNU-Linux -L../amy_talk/dist/Debug/GNU-Linux -lamy_talk -Wl,-rpath,../../tron/nety/dist/Debug/GNU-Linux -L../../tron/nety/dist/Debug/GNU-Linux -ltron_nety -Wl,-rpath,../../tron/talky/dist/Debug/GNU-Linux -L../../tron/talky/dist/Debug/GNU-Linux -ltron_talky -Wl,-rpath,../../tron/comy/dist/Debug/GNU-Linux -L../../tron/comy/dist/Debug/GNU-Linux -ltron_comy -Wl,-rpath,../../tron/tuly/dist/Debug/GNU-Linux -L../../tron/tuly/dist/Debug/GNU-Linux -ltron_tuly -Wl,-rpath,../../tron/robot/dist/Debug/GNU-Linux -L../../tron/robot/dist/Debug/GNU-Linux -ltron_robot -Wl,-rpath,../../tron/talky2/dist/Debug/GNU-Linux -L../../tron/talky2/dist/Debug/GNU-Linux -ltron_talky2 -Wl,-rpath,../../tron/wire/dist/Debug/GNU-Linux -L../../tron/wire/dist/Debug/GNU-Linux -ltron_wire -Wl,-rpath,../../tron/wire2/dist/Debug/GNU-Linux -L../../tron/wire2/dist/Debug/GNU-Linux -ltron_wire2

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ../amy_core/dist/Debug/GNU-Linux/libamy_core.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ../amy_talk/dist/Debug/GNU-Linux/libamy_talk.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ../../tron/nety/dist/Debug/GNU-Linux/libtron_nety.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ../../tron/talky/dist/Debug/GNU-Linux/libtron_talky.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ../../tron/comy/dist/Debug/GNU-Linux/libtron_comy.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ../../tron/tuly/dist/Debug/GNU-Linux/libtron_tuly.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ../../tron/robot/dist/Debug/GNU-Linux/libtron_robot.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ../../tron/talky2/dist/Debug/GNU-Linux/libtron_talky2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ../../tron/wire/dist/Debug/GNU-Linux/libtron_wire.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ../../tron/wire2/dist/Debug/GNU-Linux/libtron_wire2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/coms/AmyComs.o: src/amy/coms/AmyComs.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_talk/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/tuly/src -I../../tron/comy/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmyComs.o src/amy/coms/AmyComs.cpp

${OBJECTDIR}/src/amy/coms/ArmConnector.o: src/amy/coms/ArmConnector.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_talk/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/tuly/src -I../../tron/comy/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/ArmConnector.o src/amy/coms/ArmConnector.cpp

${OBJECTDIR}/src/amy/coms/in/ComsInArmControl.o: src/amy/coms/in/ComsInArmControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/in
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_talk/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/tuly/src -I../../tron/comy/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/in/ComsInArmControl.o src/amy/coms/in/ComsInArmControl.cpp

${OBJECTDIR}/src/amy/coms/modules/AmyBroadcaster.o: src/amy/coms/modules/AmyBroadcaster.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_talk/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/tuly/src -I../../tron/comy/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/modules/AmyBroadcaster.o src/amy/coms/modules/AmyBroadcaster.cpp

${OBJECTDIR}/src/amy/coms/modules/AmyListener.o: src/amy/coms/modules/AmyListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_talk/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/tuly/src -I../../tron/comy/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/modules/AmyListener.o src/amy/coms/modules/AmyListener.cpp

${OBJECTDIR}/src/amy/coms/out/ComsOutArmSense.o: src/amy/coms/out/ComsOutArmSense.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/out
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_talk/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/tuly/src -I../../tron/comy/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/out/ComsOutArmSense.o src/amy/coms/out/ComsOutArmSense.cpp

${OBJECTDIR}/src/amy/coms/server/ArmServer.o: src/amy/coms/server/ArmServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/server
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_talk/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/tuly/src -I../../tron/comy/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/server/ArmServer.o src/amy/coms/server/ArmServer.cpp

${OBJECTDIR}/src/amy/coms/server/AxisChannelServer.o: src/amy/coms/server/AxisChannelServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/server
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_talk/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/tuly/src -I../../tron/comy/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/server/AxisChannelServer.o src/amy/coms/server/AxisChannelServer.cpp

${OBJECTDIR}/src/amy/coms/server/CyclicChannelServer.o: src/amy/coms/server/CyclicChannelServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/server
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_talk/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/tuly/src -I../../tron/comy/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/server/CyclicChannelServer.o src/amy/coms/server/CyclicChannelServer.cpp

${OBJECTDIR}/src/amy/coms/server/ExtraChannelServer.o: src/amy/coms/server/ExtraChannelServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/server
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_talk/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/tuly/src -I../../tron/comy/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/server/ExtraChannelServer.o src/amy/coms/server/ExtraChannelServer.cpp

${OBJECTDIR}/src/amy/coms/server/JointChannelServer.o: src/amy/coms/server/JointChannelServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/server
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_talk/src -I../../tron/nety/src -I../../tron/talky/src -I../../tron/tuly/src -I../../tron/comy/src -I../../tron/robot/src -I../../tron/talky2/src -I../../tron/wire/src -I../../tron/wire2/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/server/JointChannelServer.o src/amy/coms/server/JointChannelServer.cpp

# Subprojects
.build-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_talk && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/nety && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/talky && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/comy && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/robot && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/talky2 && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/wire && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/wire2 && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_talk && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/nety && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/talky && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/comy && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/robot && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/talky2 && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/wire && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/wire2 && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

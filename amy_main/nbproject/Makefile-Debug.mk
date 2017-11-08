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
LDLIBSOPTIONS=-Wl,-rpath,../amy_core/dist/Debug/GNU-Linux -L../amy_core/dist/Debug/GNU-Linux -lamy_core -Wl,-rpath,../amy_math/dist/Debug/GNU-Linux -L../amy_math/dist/Debug/GNU-Linux -lamy_math -Wl,-rpath,../amy_move/dist/Debug/GNU-Linux -L../amy_move/dist/Debug/GNU-Linux -lamy_move -Wl,-rpath,../amy_arm/dist/Debug/GNU-Linux -L../amy_arm/dist/Debug/GNU-Linux -lamy_arm -Wl,-rpath,../amy_coms/dist/Debug/GNU-Linux -L../amy_coms/dist/Debug/GNU-Linux -lamy_coms -Wl,-rpath,../amy_talk/dist/Debug/GNU-Linux -L../amy_talk/dist/Debug/GNU-Linux -lamy_talk -Wl,-rpath,../amy_show/dist/Debug/GNU-Linux -L../amy_show/dist/Debug/GNU-Linux -lamy_show -llog4cxx -lopencv_core -lopencv_highgui -Wl,-rpath,../../tron/comy/dist/Debug/GNU-Linux -L../../tron/comy/dist/Debug/GNU-Linux -ltron_comy -Wl,-rpath,../../tron/tuly/dist/Debug/GNU-Linux -L../../tron/tuly/dist/Debug/GNU-Linux -ltron_tuly -Wl,-rpath,../../tron/talky/dist/Debug/GNU-Linux -L../../tron/talky/dist/Debug/GNU-Linux -ltron_talky -Wl,-rpath,../../tron/tivy/dist/Debug/GNU-Linux -L../../tron/tivy/dist/Debug/GNU-Linux -ltron_tivy

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_core/dist/Debug/GNU-Linux/libamy_core.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_math/dist/Debug/GNU-Linux/libamy_math.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_move/dist/Debug/GNU-Linux/libamy_move.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_arm/dist/Debug/GNU-Linux/libamy_arm.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_coms/dist/Debug/GNU-Linux/libamy_coms.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_talk/dist/Debug/GNU-Linux/libamy_talk.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../amy_show/dist/Debug/GNU-Linux/libamy_show.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/comy/dist/Debug/GNU-Linux/libtron_comy.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/tuly/dist/Debug/GNU-Linux/libtron_tuly.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/talky/dist/Debug/GNU-Linux/libtron_talky.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ../../tron/tivy/dist/Debug/GNU-Linux/libtron_tivy.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/amy/main/AmyControl.o: src/amy/main/AmyControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_math/src -I../amy_move/src -I../amy_arm/src -I../amy_coms/src -I../amy_talk/src -I../amy_show/src -I../../tron/comy/src -I../../tron/tuly/src -I../../tron/talky/src -I../../tron/tivy/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/AmyControl.o src/amy/main/AmyControl.cpp

${OBJECTDIR}/src/amy/main/ArmTest.o: src/amy/main/ArmTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_math/src -I../amy_move/src -I../amy_arm/src -I../amy_coms/src -I../amy_talk/src -I../amy_show/src -I../../tron/comy/src -I../../tron/tuly/src -I../../tron/talky/src -I../../tron/tivy/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/ArmTest.o src/amy/main/ArmTest.cpp

${OBJECTDIR}/src/amy/main/main.o: src/amy/main/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_math/src -I../amy_move/src -I../amy_arm/src -I../amy_coms/src -I../amy_talk/src -I../amy_show/src -I../../tron/comy/src -I../../tron/tuly/src -I../../tron/talky/src -I../../tron/tivy/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/main.o src/amy/main/main.cpp

${OBJECTDIR}/src/amy/main/robots/ArmUR5.o: src/amy/main/robots/ArmUR5.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_math/src -I../amy_move/src -I../amy_arm/src -I../amy_coms/src -I../amy_talk/src -I../amy_show/src -I../../tron/comy/src -I../../tron/tuly/src -I../../tron/talky/src -I../../tron/tivy/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/ArmUR5.o src/amy/main/robots/ArmUR5.cpp

${OBJECTDIR}/src/amy/main/robots/ArmYoubot.o: src/amy/main/robots/ArmYoubot.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_math/src -I../amy_move/src -I../amy_arm/src -I../amy_coms/src -I../amy_talk/src -I../amy_show/src -I../../tron/comy/src -I../../tron/tuly/src -I../../tron/talky/src -I../../tron/tivy/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/ArmYoubot.o src/amy/main/robots/ArmYoubot.cpp

${OBJECTDIR}/src/amy/main/robots/SupportedRobots.o: src/amy/main/robots/SupportedRobots.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/main/robots
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../amy_math/src -I../amy_move/src -I../amy_arm/src -I../amy_coms/src -I../amy_talk/src -I../amy_show/src -I../../tron/comy/src -I../../tron/tuly/src -I../../tron/talky/src -I../../tron/tivy/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/main/robots/SupportedRobots.o src/amy/main/robots/SupportedRobots.cpp

# Subprojects
.build-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_math && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_move && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_coms && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_talk && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_show && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/comy && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/talky && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tivy && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy

# Subprojects
.clean-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_math && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_move && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_coms && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_talk && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_show && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/comy && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/talky && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tivy && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

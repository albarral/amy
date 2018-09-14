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
	${OBJECTDIR}/src/amy/test/ArmTest.o \
	${OBJECTDIR}/src/amy/test/main.o


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
LDLIBSOPTIONS=-Wl,-rpath,../amy_arm/dist/Debug/GNU-Linux -L../amy_arm/dist/Debug/GNU-Linux -lamy_arm -Wl,-rpath,../amy_interface2/dist/Debug/GNU-Linux -L../amy_interface2/dist/Debug/GNU-Linux -lamy_interface2 -Wl,-rpath,../../tron/tron_coms/dist/Debug/GNU-Linux -L../../tron/tron_coms/dist/Debug/GNU-Linux -ltron_coms -Wl,-rpath,../../tron/tron_topics/dist/Debug/GNU-Linux -L../../tron/tron_topics/dist/Debug/GNU-Linux -ltron_topics -Wl,-rpath,../../tron/tron_util/dist/Debug/GNU-Linux -L../../tron/tron_util/dist/Debug/GNU-Linux -ltron_util -Wl,-rpath,../../tron/tron_math/dist/Debug/GNU-Linux -L../../tron/tron_math/dist/Debug/GNU-Linux -ltron_math -lignition-math2 -lignition-msgs0 -lignition-transport3 -llog4cxx

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_test

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_test: ../amy_arm/dist/Debug/GNU-Linux/libamy_arm.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_test: ../amy_interface2/dist/Debug/GNU-Linux/libamy_interface2.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_test: ../../tron/tron_coms/dist/Debug/GNU-Linux/libtron_coms.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_test: ../../tron/tron_topics/dist/Debug/GNU-Linux/libtron_topics.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_test: ../../tron/tron_util/dist/Debug/GNU-Linux/libtron_util.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_test: ../../tron/tron_math/dist/Debug/GNU-Linux/libtron_math.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_test: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_test ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/amy/test/ArmTest.o: src/amy/test/ArmTest.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_arm/src -I../amy_interface2/src -I../../tron/tron_coms/src -I../../tron/tron_topics/src -I../../tron/tron_util/src -I../../tron/tron_math/src -I/usr/include/ignition/transport3 -I/usr/include/ignition/msgs0 -I/usr/include/ignition/math2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/test/ArmTest.o src/amy/test/ArmTest.cpp

${OBJECTDIR}/src/amy/test/main.o: src/amy/test/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/test
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_arm/src -I../amy_interface2/src -I../../tron/tron_coms/src -I../../tron/tron_topics/src -I../../tron/tron_util/src -I../../tron/tron_math/src -I/usr/include/ignition/transport3 -I/usr/include/ignition/msgs0 -I/usr/include/ignition/math2 -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/test/main.o src/amy/test/main.cpp

# Subprojects
.build-subprojects:
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug
	cd ../amy_interface2 && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_coms && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_topics && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_util && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tron_math && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/amy_test

# Subprojects
.clean-subprojects:
	cd ../amy_arm && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../amy_interface2 && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_coms && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_topics && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_util && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tron_math && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

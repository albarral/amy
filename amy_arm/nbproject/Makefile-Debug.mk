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
	${OBJECTDIR}/src/amy/arm/ArmManager.o \
	${OBJECTDIR}/src/amy/arm/config/ArmConfig.o \
	${OBJECTDIR}/src/amy/arm/modules/ArmSense.o \
	${OBJECTDIR}/src/amy/arm/modules/AxisDriver.o \
	${OBJECTDIR}/src/amy/arm/modules/AxisRacer.o \
	${OBJECTDIR}/src/amy/arm/modules/FrontalCycler.o \
	${OBJECTDIR}/src/amy/arm/modules/JointDriver.o \
	${OBJECTDIR}/src/amy/arm/modules/PanDriver.o \
	${OBJECTDIR}/src/amy/arm/modules/PanRacer.o \
	${OBJECTDIR}/src/amy/arm/modules/RadialRacer.o \
	${OBJECTDIR}/src/amy/arm/modules/RadiusDriver.o \
	${OBJECTDIR}/src/amy/arm/modules/TiltDriver.o \
	${OBJECTDIR}/src/amy/arm/modules/TiltKeeper.o \
	${OBJECTDIR}/src/amy/arm/modules/TiltRacer.o \
	${OBJECTDIR}/src/amy/arm/move/JointAccelerator.o \
	${OBJECTDIR}/src/amy/arm/move/JointPositioner.o \
	${OBJECTDIR}/src/amy/arm/move/RadialPositioner.o \
	${OBJECTDIR}/src/amy/arm/move/SpeedSensor3.o \
	${OBJECTDIR}/src/amy/arm/util/ArmModule.o \
	${OBJECTDIR}/src/amy/arm/util/ArmModule3.o \
	${OBJECTDIR}/src/amy/arm/util/JointModule.o


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
LDLIBSOPTIONS=-Wl,-rpath,../amy_core/dist/Debug/GNU-Linux -L../amy_core/dist/Debug/GNU-Linux -lamy_core -Wl,-rpath,../../tron/tuly/dist/Debug/GNU-Linux -L../../tron/tuly/dist/Debug/GNU-Linux -ltron_tuly -Wl,-rpath,../../tron/maty/dist/Debug/GNU-Linux -L../../tron/maty/dist/Debug/GNU-Linux -ltron_maty

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_arm.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_arm.${CND_DLIB_EXT}: ../amy_core/dist/Debug/GNU-Linux/libamy_core.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_arm.${CND_DLIB_EXT}: ../../tron/tuly/dist/Debug/GNU-Linux/libtron_tuly.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_arm.${CND_DLIB_EXT}: ../../tron/maty/dist/Debug/GNU-Linux/libtron_maty.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_arm.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_arm.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/arm/ArmManager.o: src/amy/arm/ArmManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/ArmManager.o src/amy/arm/ArmManager.cpp

${OBJECTDIR}/src/amy/arm/config/ArmConfig.o: src/amy/arm/config/ArmConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/config
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/config/ArmConfig.o src/amy/arm/config/ArmConfig.cpp

${OBJECTDIR}/src/amy/arm/modules/ArmSense.o: src/amy/arm/modules/ArmSense.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/ArmSense.o src/amy/arm/modules/ArmSense.cpp

${OBJECTDIR}/src/amy/arm/modules/AxisDriver.o: src/amy/arm/modules/AxisDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/AxisDriver.o src/amy/arm/modules/AxisDriver.cpp

${OBJECTDIR}/src/amy/arm/modules/AxisRacer.o: src/amy/arm/modules/AxisRacer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/AxisRacer.o src/amy/arm/modules/AxisRacer.cpp

${OBJECTDIR}/src/amy/arm/modules/FrontalCycler.o: src/amy/arm/modules/FrontalCycler.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/FrontalCycler.o src/amy/arm/modules/FrontalCycler.cpp

${OBJECTDIR}/src/amy/arm/modules/JointDriver.o: src/amy/arm/modules/JointDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/JointDriver.o src/amy/arm/modules/JointDriver.cpp

${OBJECTDIR}/src/amy/arm/modules/PanDriver.o: src/amy/arm/modules/PanDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/PanDriver.o src/amy/arm/modules/PanDriver.cpp

${OBJECTDIR}/src/amy/arm/modules/PanRacer.o: src/amy/arm/modules/PanRacer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/PanRacer.o src/amy/arm/modules/PanRacer.cpp

${OBJECTDIR}/src/amy/arm/modules/RadialRacer.o: src/amy/arm/modules/RadialRacer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/RadialRacer.o src/amy/arm/modules/RadialRacer.cpp

${OBJECTDIR}/src/amy/arm/modules/RadiusDriver.o: src/amy/arm/modules/RadiusDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/RadiusDriver.o src/amy/arm/modules/RadiusDriver.cpp

${OBJECTDIR}/src/amy/arm/modules/TiltDriver.o: src/amy/arm/modules/TiltDriver.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/TiltDriver.o src/amy/arm/modules/TiltDriver.cpp

${OBJECTDIR}/src/amy/arm/modules/TiltKeeper.o: src/amy/arm/modules/TiltKeeper.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/TiltKeeper.o src/amy/arm/modules/TiltKeeper.cpp

${OBJECTDIR}/src/amy/arm/modules/TiltRacer.o: src/amy/arm/modules/TiltRacer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/modules/TiltRacer.o src/amy/arm/modules/TiltRacer.cpp

${OBJECTDIR}/src/amy/arm/move/JointAccelerator.o: src/amy/arm/move/JointAccelerator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/JointAccelerator.o src/amy/arm/move/JointAccelerator.cpp

${OBJECTDIR}/src/amy/arm/move/JointPositioner.o: src/amy/arm/move/JointPositioner.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/JointPositioner.o src/amy/arm/move/JointPositioner.cpp

${OBJECTDIR}/src/amy/arm/move/RadialPositioner.o: src/amy/arm/move/RadialPositioner.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/RadialPositioner.o src/amy/arm/move/RadialPositioner.cpp

${OBJECTDIR}/src/amy/arm/move/SpeedSensor3.o: src/amy/arm/move/SpeedSensor3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/move
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/move/SpeedSensor3.o src/amy/arm/move/SpeedSensor3.cpp

${OBJECTDIR}/src/amy/arm/util/ArmModule.o: src/amy/arm/util/ArmModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/util
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/util/ArmModule.o src/amy/arm/util/ArmModule.cpp

${OBJECTDIR}/src/amy/arm/util/ArmModule3.o: src/amy/arm/util/ArmModule3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/util
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/util/ArmModule3.o src/amy/arm/util/ArmModule3.cpp

${OBJECTDIR}/src/amy/arm/util/JointModule.o: src/amy/arm/util/JointModule.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/arm/util
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../amy_core/src -I../../tron/tuly/src -I../../tron/maty/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/arm/util/JointModule.o src/amy/arm/util/JointModule.cpp

# Subprojects
.build-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_arm.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../amy_core && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/tuly && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../../tron/maty && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

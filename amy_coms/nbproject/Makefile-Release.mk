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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/amy/coms/AmyClient.o \
	${OBJECTDIR}/src/amy/coms/AmyComsConfig.o \
	${OBJECTDIR}/src/amy/coms/AmyPublisher.o \
	${OBJECTDIR}/src/amy/coms/AmyServer.o \
	${OBJECTDIR}/src/amy/coms/AmySubscriber.o \
	${OBJECTDIR}/src/amy/coms/ComsInterpreter.o \
	${OBJECTDIR}/src/amy/coms/data/AmyCommand.o \
	${OBJECTDIR}/src/amy/coms/data/ArmData.o \
	${OBJECTDIR}/src/amy/coms/data/AxisCommand.o \
	${OBJECTDIR}/src/amy/coms/data/CyclicCommand.o \
	${OBJECTDIR}/src/amy/coms/data/JointCommand.o \
	${OBJECTDIR}/src/amy/coms/data/OtherCommand.o \
	${OBJECTDIR}/src/amy/coms/dictionary/AxisCategory.o \
	${OBJECTDIR}/src/amy/coms/dictionary/ComsCategory.o \
	${OBJECTDIR}/src/amy/coms/dictionary/ComsCommand.o \
	${OBJECTDIR}/src/amy/coms/dictionary/ComsDictionary.o \
	${OBJECTDIR}/src/amy/coms/dictionary/CyclicCategory.o \
	${OBJECTDIR}/src/amy/coms/dictionary/JointCategory.o \
	${OBJECTDIR}/src/amy/coms/dictionary/OtherCategory.o \
	${OBJECTDIR}/src/amy/coms/file/AmyFileClient.o \
	${OBJECTDIR}/src/amy/coms/file/AmyFilePublisher.o \
	${OBJECTDIR}/src/amy/coms/file/AmyFileServer.o \
	${OBJECTDIR}/src/amy/coms/file/AmyFileSubscriber.o \
	${OBJECTDIR}/src/amy/coms/sections/AxisClient.o \
	${OBJECTDIR}/src/amy/coms/sections/AxisServer.o \
	${OBJECTDIR}/src/amy/coms/sections/CyclicClient.o \
	${OBJECTDIR}/src/amy/coms/sections/CyclicServer.o \
	${OBJECTDIR}/src/amy/coms/sections/JointClient.o \
	${OBJECTDIR}/src/amy/coms/sections/JointServer.o \
	${OBJECTDIR}/src/amy/coms/sections/OtherClient.o \
	${OBJECTDIR}/src/amy/coms/sections/OtherServer.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/coms/AmyClient.o: src/amy/coms/AmyClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmyClient.o src/amy/coms/AmyClient.cpp

${OBJECTDIR}/src/amy/coms/AmyComsConfig.o: src/amy/coms/AmyComsConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmyComsConfig.o src/amy/coms/AmyComsConfig.cpp

${OBJECTDIR}/src/amy/coms/AmyPublisher.o: src/amy/coms/AmyPublisher.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmyPublisher.o src/amy/coms/AmyPublisher.cpp

${OBJECTDIR}/src/amy/coms/AmyServer.o: src/amy/coms/AmyServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmyServer.o src/amy/coms/AmyServer.cpp

${OBJECTDIR}/src/amy/coms/AmySubscriber.o: src/amy/coms/AmySubscriber.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/AmySubscriber.o src/amy/coms/AmySubscriber.cpp

${OBJECTDIR}/src/amy/coms/ComsInterpreter.o: src/amy/coms/ComsInterpreter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/ComsInterpreter.o src/amy/coms/ComsInterpreter.cpp

${OBJECTDIR}/src/amy/coms/data/AmyCommand.o: src/amy/coms/data/AmyCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/data/AmyCommand.o src/amy/coms/data/AmyCommand.cpp

${OBJECTDIR}/src/amy/coms/data/ArmData.o: src/amy/coms/data/ArmData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/data/ArmData.o src/amy/coms/data/ArmData.cpp

${OBJECTDIR}/src/amy/coms/data/AxisCommand.o: src/amy/coms/data/AxisCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/data/AxisCommand.o src/amy/coms/data/AxisCommand.cpp

${OBJECTDIR}/src/amy/coms/data/CyclicCommand.o: src/amy/coms/data/CyclicCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/data/CyclicCommand.o src/amy/coms/data/CyclicCommand.cpp

${OBJECTDIR}/src/amy/coms/data/JointCommand.o: src/amy/coms/data/JointCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/data/JointCommand.o src/amy/coms/data/JointCommand.cpp

${OBJECTDIR}/src/amy/coms/data/OtherCommand.o: src/amy/coms/data/OtherCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/data/OtherCommand.o src/amy/coms/data/OtherCommand.cpp

${OBJECTDIR}/src/amy/coms/dictionary/AxisCategory.o: src/amy/coms/dictionary/AxisCategory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/dictionary
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/dictionary/AxisCategory.o src/amy/coms/dictionary/AxisCategory.cpp

${OBJECTDIR}/src/amy/coms/dictionary/ComsCategory.o: src/amy/coms/dictionary/ComsCategory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/dictionary
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/dictionary/ComsCategory.o src/amy/coms/dictionary/ComsCategory.cpp

${OBJECTDIR}/src/amy/coms/dictionary/ComsCommand.o: src/amy/coms/dictionary/ComsCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/dictionary
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/dictionary/ComsCommand.o src/amy/coms/dictionary/ComsCommand.cpp

${OBJECTDIR}/src/amy/coms/dictionary/ComsDictionary.o: src/amy/coms/dictionary/ComsDictionary.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/dictionary
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/dictionary/ComsDictionary.o src/amy/coms/dictionary/ComsDictionary.cpp

${OBJECTDIR}/src/amy/coms/dictionary/CyclicCategory.o: src/amy/coms/dictionary/CyclicCategory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/dictionary
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/dictionary/CyclicCategory.o src/amy/coms/dictionary/CyclicCategory.cpp

${OBJECTDIR}/src/amy/coms/dictionary/JointCategory.o: src/amy/coms/dictionary/JointCategory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/dictionary
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/dictionary/JointCategory.o src/amy/coms/dictionary/JointCategory.cpp

${OBJECTDIR}/src/amy/coms/dictionary/OtherCategory.o: src/amy/coms/dictionary/OtherCategory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/dictionary
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/dictionary/OtherCategory.o src/amy/coms/dictionary/OtherCategory.cpp

${OBJECTDIR}/src/amy/coms/file/AmyFileClient.o: src/amy/coms/file/AmyFileClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/file
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/file/AmyFileClient.o src/amy/coms/file/AmyFileClient.cpp

${OBJECTDIR}/src/amy/coms/file/AmyFilePublisher.o: src/amy/coms/file/AmyFilePublisher.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/file
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/file/AmyFilePublisher.o src/amy/coms/file/AmyFilePublisher.cpp

${OBJECTDIR}/src/amy/coms/file/AmyFileServer.o: src/amy/coms/file/AmyFileServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/file
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/file/AmyFileServer.o src/amy/coms/file/AmyFileServer.cpp

${OBJECTDIR}/src/amy/coms/file/AmyFileSubscriber.o: src/amy/coms/file/AmyFileSubscriber.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/file
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/file/AmyFileSubscriber.o src/amy/coms/file/AmyFileSubscriber.cpp

${OBJECTDIR}/src/amy/coms/sections/AxisClient.o: src/amy/coms/sections/AxisClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/sections
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/sections/AxisClient.o src/amy/coms/sections/AxisClient.cpp

${OBJECTDIR}/src/amy/coms/sections/AxisServer.o: src/amy/coms/sections/AxisServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/sections
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/sections/AxisServer.o src/amy/coms/sections/AxisServer.cpp

${OBJECTDIR}/src/amy/coms/sections/CyclicClient.o: src/amy/coms/sections/CyclicClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/sections
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/sections/CyclicClient.o src/amy/coms/sections/CyclicClient.cpp

${OBJECTDIR}/src/amy/coms/sections/CyclicServer.o: src/amy/coms/sections/CyclicServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/sections
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/sections/CyclicServer.o src/amy/coms/sections/CyclicServer.cpp

${OBJECTDIR}/src/amy/coms/sections/JointClient.o: src/amy/coms/sections/JointClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/sections
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/sections/JointClient.o src/amy/coms/sections/JointClient.cpp

${OBJECTDIR}/src/amy/coms/sections/JointServer.o: src/amy/coms/sections/JointServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/sections
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/sections/JointServer.o src/amy/coms/sections/JointServer.cpp

${OBJECTDIR}/src/amy/coms/sections/OtherClient.o: src/amy/coms/sections/OtherClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/sections
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/sections/OtherClient.o src/amy/coms/sections/OtherClient.cpp

${OBJECTDIR}/src/amy/coms/sections/OtherServer.o: src/amy/coms/sections/OtherServer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/coms/sections
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/coms/sections/OtherServer.o src/amy/coms/sections/OtherServer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_coms.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

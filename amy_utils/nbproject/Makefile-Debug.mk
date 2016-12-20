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
	${OBJECTDIR}/src/amy/utils/Click.o \
	${OBJECTDIR}/src/amy/utils/Console.o \
	${OBJECTDIR}/src/amy/utils/File.o \
	${OBJECTDIR}/src/amy/utils/FileReader.o \
	${OBJECTDIR}/src/amy/utils/FileWriter.o \
	${OBJECTDIR}/src/amy/utils/Record.o \
	${OBJECTDIR}/src/amy/utils/module.o \
	${OBJECTDIR}/src/amy/utils/module2.o \
	${OBJECTDIR}/src/amy/utils/module3.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_utils.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_utils.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_utils.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/utils/Click.o: src/amy/utils/Click.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/utils/Click.o src/amy/utils/Click.cpp

${OBJECTDIR}/src/amy/utils/Console.o: src/amy/utils/Console.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/utils/Console.o src/amy/utils/Console.cpp

${OBJECTDIR}/src/amy/utils/File.o: src/amy/utils/File.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/utils/File.o src/amy/utils/File.cpp

${OBJECTDIR}/src/amy/utils/FileReader.o: src/amy/utils/FileReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/utils/FileReader.o src/amy/utils/FileReader.cpp

${OBJECTDIR}/src/amy/utils/FileWriter.o: src/amy/utils/FileWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/utils/FileWriter.o src/amy/utils/FileWriter.cpp

${OBJECTDIR}/src/amy/utils/Record.o: src/amy/utils/Record.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/utils/Record.o src/amy/utils/Record.cpp

${OBJECTDIR}/src/amy/utils/module.o: src/amy/utils/module.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/utils/module.o src/amy/utils/module.cpp

${OBJECTDIR}/src/amy/utils/module2.o: src/amy/utils/module2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/utils/module2.o src/amy/utils/module2.cpp

${OBJECTDIR}/src/amy/utils/module3.o: src/amy/utils/module3.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/utils/module3.o src/amy/utils/module3.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_utils.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

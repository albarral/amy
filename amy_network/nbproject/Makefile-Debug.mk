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
	${OBJECTDIR}/src/amy/network/ArmNetwork.o \
	${OBJECTDIR}/src/amy/network/config/NetworkConfig.o \
	${OBJECTDIR}/src/amy/network/db/DBClient.o \
	${OBJECTDIR}/src/amy/network/db/DBConnection.o \
	${OBJECTDIR}/src/amy/network/db/Database.o


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
LDLIBSOPTIONS=-llog4cxx -lmysqlcppconn

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_network.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_network.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_network.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/amy/network/ArmNetwork.o: src/amy/network/ArmNetwork.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/network
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/network/ArmNetwork.o src/amy/network/ArmNetwork.cpp

${OBJECTDIR}/src/amy/network/config/NetworkConfig.o: src/amy/network/config/NetworkConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/network/config
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/network/config/NetworkConfig.o src/amy/network/config/NetworkConfig.cpp

${OBJECTDIR}/src/amy/network/db/DBClient.o: src/amy/network/db/DBClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/network/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/network/db/DBClient.o src/amy/network/db/DBClient.cpp

${OBJECTDIR}/src/amy/network/db/DBConnection.o: src/amy/network/db/DBConnection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/network/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/network/db/DBConnection.o src/amy/network/db/DBConnection.cpp

${OBJECTDIR}/src/amy/network/db/Database.o: src/amy/network/db/Database.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/amy/network/db
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/amy/network/db/Database.o src/amy/network/db/Database.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libamy_network.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc

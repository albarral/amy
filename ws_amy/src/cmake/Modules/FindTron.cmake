# Files finder for tron libraries
# This finder obtains the following variables:
#  TRON_FOUND - System has the package
#  TRON_INCLUDE_DIRS - The include directories
#  TRON_LIBRARIES - The libraries needed

# required tron libs: 
# - tron_coms   (libtron_coms.so)
# - tron_interface   (libtron_interface.so)
# - tron_topics  (libtron_topics.so)
# - tron_util  (libtron_util.so)

set (TRON_HOME /home/albarral/DEV/tron)
set (TARGET_SYSTEM Debug/GNU-Linux)

find_path(tron_coms_INC tron/coms/ComsChannel.h  PATHS ${TRON_HOME}/tron_coms/src)
mark_as_advanced(tron_coms_INC)
find_path(tron_interface_INC tron/interface/SectionListener.h  PATHS ${TRON_HOME}/tron_interface/src)
mark_as_advanced(tron_interface_INC)
find_path(tron_topics_INC tron/topics/Topic.h  PATHS ${TRON_HOME}/tron_topics/src)
mark_as_advanced(tron_topics_INC)
find_path(tron_util_INC tron/util/CodeMap.h  PATHS ${TRON_HOME}/tron_util/src)
mark_as_advanced(tron_util_INC)

find_library(tron_coms_LIB tron_coms PATHS ${TRON_HOME}/tron_coms/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
mark_as_advanced(tron_coms_LIB)
find_library(tron_interface_LIB tron_interface PATHS ${TRON_HOME}/tron_interface/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
mark_as_advanced(tron_interface_LIB)
find_library(tron_topics_LIB tron_topics PATHS ${TRON_HOME}/tron_topics/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
mark_as_advanced(tron_topics_LIB)
find_library(tron_util_LIB tron_util PATHS ${TRON_HOME}/tron_util/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
mark_as_advanced(tron_util_LIB)


# handle the QUIETLY and REQUIRED arguments and set TRON_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TRON
                                  REQUIRED_VARS tron_coms_INC tron_interface_INC tron_topics_INC tron_util_INC 
						tron_coms_LIB tron_interface_LIB tron_topics_LIB tron_util_LIB)

if(TRON_FOUND)
	set(TRON_LIBRARIES      ${tron_coms_LIB} ${tron_interface_LIB} ${tron_topics_LIB} ${tron_util_LIB})
	set(TRON_INCLUDE_DIRS   ${tron_coms_INC} ${tron_interface_INC} ${tron_topics_INC} ${tron_util_INC})
endif()


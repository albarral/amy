# Files finder for tron libraries
# This finder obtains the following variables:
#  tron_FOUND - System has the package
#  tron_INCLUDE_DIRS - The include directories
#  tron_LIBRARIES - The libraries needed

# required tron libs: 
# - tron_coms   (libtron_coms.so)
# - tron_topics  (libtron_topics.so)
# - tron_util  (libtron_util.so)

set (TRON_HOME /home/albarral/DEV/tron)
set (TARGET_SYSTEM Debug/GNU-Linux)

find_path(tron_coms_INC tron/coms/ComsChannel.h  PATHS ${TRON_HOME}/tron_coms/src)
find_path(tron_topics_INC tron/topics/Topic.h  PATHS ${TRON_HOME}/tron_topics/src)
find_path(tron_util_INC tron/util/CodeMap.h  PATHS ${TRON_HOME}/tron_util/src)

find_library(tron_coms_LIB tron_coms PATHS ${TRON_HOME}/tron_coms/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(tron_topics_LIB tron_topics PATHS ${TRON_HOME}/tron_topics/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(tron_util_LIB tron_util PATHS ${TRON_HOME}/tron_util/dist  PATH_SUFFIXES ${TARGET_SYSTEM})

# ALL TOGETHER ...
# set(module_LIBRARIES     ${x_LIB} ${y_LIB} ...)
# set(module_INCLUDE_DIRS     ${x_INC} ${y_INC} ...)
set(tron_LIBRARIES      ${tron_coms_LIB} ${tron_topics_LIB} ${tron_util_LIB})
set(tron_INCLUDE_DIRS   ${tron_coms_INC} ${tron_topics_INC} ${tron_util_INC})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set module_FOUND to TRUE if all listed variables are TRUE
find_package_handle_standard_args(tron DEFAULT_MSG tron_coms_INC tron_topics_INC tron_util_INC tron_coms_LIB tron_topics_LIB tron_util_LIB)

mark_as_advanced(tron_coms_INC tron_topics_INC tron_util_INC tron_coms_LIB tron_topics_LIB tron_util_LIB)



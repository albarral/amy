# Files finder for tron libraries
# This finder obtains the following variables:
#  tron_FOUND - System has the package
#  tron_INCLUDE_DIRS - The include directories
#  tron_LIBRARIES - The libraries needed

# required tron libs: 
# - tron_util  (libtron_util.so)
# - tron_tools  (libtron_tools.so)
# - tron_wire   (libtron_wire.so)
# - tron_wire2  (libtron_wire2.so)

set (TRON_HOME /home/albarral/DEV/tron)
set (TARGET_SYSTEM Debug/GNU-Linux)

find_path(tron_util_INC tron/util/CodeMap.h  PATHS ${TRON_HOME}/tron_util/src)
find_path(tron_tools_INC tron/tools/FileReader.h  PATHS ${TRON_HOME}/tron_tools/src)
find_path(tron_wire_INC tron/wire/Wire.h  PATHS ${TRON_HOME}/tron_wire/src)
find_path(tron_wire2_INC tron/wire2/FileWire.h  PATHS ${TRON_HOME}/tron_wire2/src)

find_library(tron_util_LIB tron_util PATHS ${TRON_HOME}/tron_util/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(tron_tools_LIB tron_tools PATHS ${TRON_HOME}/tron_tools/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(tron_wire_LIB tron_wire PATHS ${TRON_HOME}/tron_wire/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(tron_wire2_LIB tron_wire2 PATHS ${TRON_HOME}/tron_wire2/dist  PATH_SUFFIXES ${TARGET_SYSTEM})

# ALL TOGETHER ...
# set(module_LIBRARIES     ${x_LIB} ${y_LIB} ...)
# set(module_INCLUDE_DIRS     ${x_INC} ${y_INC} ...)
set(tron_LIBRARIES      ${tron_util_LIB} ${tron_tools_LIB} ${tron_wire_LIB} ${tron_wire2_LIB})
set(tron_INCLUDE_DIRS   ${tron_util_INC} ${tron_tools_INC} ${tron_wire_INC} ${tron_wire2_INC})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set module_FOUND to TRUE if all listed variables are TRUE
find_package_handle_standard_args(tron DEFAULT_MSG tron_util_INC tron_tools_INC tron_wire_INC tron_wire2_INC tron_util_LIB tron_tools_LIB tron_wire_LIB tron_wire2_LIB)

mark_as_advanced(tron_util_INC tron_tools_INC tron_wire_INC2 tron_wire_INC tron_util_LIB tron_tools_LIB tron_wire_LIB tron_wire2_LIB)



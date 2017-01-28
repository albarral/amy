# - Try to find amy package (for arm control)
# Once done this will define
#  amy_FOUND - System has the package
#  amy_INCLUDE_DIRS - The include directories
#  amy_LIBRARIES - The libraries needed

# required modules from amy package: 
# - amy_core   (libamy_core.so)
# - amy_utils   (libamy_utils.so)
# - amy_coms (libamy_coms.so)

set (AMY_HOME /home/oriol/amy)
set (TARGET_SYSTEM Debug/GNU-Linux)

find_path(amy_core_INC  amy/core/robot/Arm.h  PATHS ${AMY_HOME}/amy_core/src)
find_path(amy_utils_INC  amy/utils/File.h  PATHS ${AMY_HOME}/amy_utils/src)
find_path(amy_coms_INC  amy/coms/AmyPublisher.h  PATHS ${AMY_HOME}/amy_coms/src)

find_library(amy_core_LIB  amy_core  PATHS ${AMY_HOME}/amy_core/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(amy_utils_LIB  amy_utils  PATHS ${AMY_HOME}/amy_utils/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(amy_coms_LIB  amy_coms  PATHS ${AMY_HOME}/amy_coms/dist  PATH_SUFFIXES ${TARGET_SYSTEM})

# ALL TOGETHER ...
# set(module_LIBRARIES     ${x_LIB} ${y_LIB} ...)
# set(module_INCLUDE_DIRS     ${x_INC} ${y_INC} ...)
set(amy_LIBRARIES      ${amy_core_LIB} ${amy_utils_LIB} ${amy_coms_LIB})
set(amy_INCLUDE_DIRS   ${amy_core_INC} ${amy_utils_INC} ${amy_coms_INC})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set module_FOUND to TRUE if all listed variables are TRUE
find_package_handle_standard_args(amy DEFAULT_MSG amy_core_INC amy_utils_INC amy_coms_INC amy_core_LIB amy_utils_LIB amy_coms_LIB)

mark_as_advanced(amy_core_INC amy_utils_INC amy_coms_INC amy_core_LIB amy_utils_LIB amy_coms_LIB)



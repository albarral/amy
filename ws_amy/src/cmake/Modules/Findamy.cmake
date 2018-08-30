# Files finder for amy_interface library
# This finder obtains the following variables:
#  amy_FOUND - System has the package
#  amy_INCLUDE_DIRS - The include directories
#  amy_LIBRARIES - The libraries needed

# required amy libs: 
# - amy_interface2   (libamy_interface2.so)

set (amy_HOME /home/albarral/DEV/amy)
set (TARGET_SYSTEM Debug/GNU-Linux)

find_path(amy_interface2_INC amy/interface2/ArmNode.h  PATHS ${amy_HOME}/amy_interface2/src)

find_library(amy_interface2_LIB amy_interface2  PATHS ${amy_HOME}/amy_interface2/dist  PATH_SUFFIXES ${TARGET_SYSTEM})

# ALL TOGETHER ...
# set(module_LIBRARIES     ${x_LIB} ${y_LIB} ...)
# set(module_INCLUDE_DIRS     ${x_INC} ${y_INC} ...)
set(amy_LIBRARIES      ${amy_interface2_LIB})
set(amy_INCLUDE_DIRS   ${amy_interface2_INC})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set module_FOUND to TRUE if all listed variables are TRUE
find_package_handle_standard_args(amy DEFAULT_MSG amy_interface2_INC amy_interface2_LIB)

mark_as_advanced(amy_interface2_INC amy_interface2_LIB)



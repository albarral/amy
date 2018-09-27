# Files finder for amy_interface library
# This finder obtains the following variables:
#  AMY_FOUND - System has the package
#  AMY_INCLUDE_DIRS - The include directories
#  AMY_LIBRARIES - The libraries needed

# required amy libs: 
# - amy_interface2   (libamy_interface2.so)

set (amy_HOME /home/albarral/DEV/amy)
set (TARGET_SYSTEM Debug/GNU-Linux)

find_path(amy_interface2_INC amy/interface2/ArmNode.h  PATHS ${amy_HOME}/amy_interface2/src)
mark_as_advanced(amy_interface2_INC)

find_library(amy_interface2_LIB amy_interface2  PATHS ${amy_HOME}/amy_interface2/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
mark_as_advanced(amy_interface2_LIB)

# handle the QUIETLY and REQUIRED arguments and set TRON_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(AMY
                                  REQUIRED_VARS amy_interface2_INC amy_interface2_LIB)

if(AMY_FOUND)
	set(AMY_LIBRARIES ${amy_interface2_LIB})
	set(AMY_INCLUDE_DIRS ${amy_interface2_INC})
endif()


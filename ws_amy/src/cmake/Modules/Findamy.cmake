# - Try to find amy talk lib
# Once done this will define
#  amy_FOUND - System has the package
#  amy_INCLUDE_DIRS - The include directories
#  amy_LIBRARIES - The libraries needed

# required modules from amy package: 
# - amy_talk  (libamy_talk.so)

set (amy_HOME /home/albarral/DEV/amy)
set (TARGET_SYSTEM Debug/GNU-Linux)

find_path(amy_talk_INC amy/talk/DataBlockJoints.h  PATHS ${amy_HOME}/amy_talk/src)

find_library(amy_talk_LIB amy_talk  PATHS ${amy_HOME}/amy_talk/dist  PATH_SUFFIXES ${TARGET_SYSTEM})

# ALL TOGETHER ...
# set(module_LIBRARIES     ${x_LIB} ${y_LIB} ...)
# set(module_INCLUDE_DIRS     ${x_INC} ${y_INC} ...)
set(amy_LIBRARIES      ${amy_talk_LIB})
set(amy_INCLUDE_DIRS   ${amy_talk_INC})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set module_FOUND to TRUE if all listed variables are TRUE
find_package_handle_standard_args(amy DEFAULT_MSG amy_talk_INC amy_talk_LIB)

mark_as_advanced(amy_talk_INC amy_talk_LIB)



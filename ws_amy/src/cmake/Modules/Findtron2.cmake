# Files finder for tron2 libraries
# This finder obtains the following variables:
#  tron2_FOUND - System has the package
#  tron2_INCLUDE_DIRS - The include directories
#  tron2_LIBRARIES - The libraries needed

# required tron2 libs: 
# - tron2_robot   (libtron2_robot.so)
# - tron2_talky  (libtron2_talky.so)

set (tron2_HOME /home/albarral/DEV/tron2)
set (TARGET_SYSTEM Debug/GNU-Linux)

find_path(tron2_robot_INC tron2/robot/RobotNodes.h  PATHS ${tron2_HOME}/tron2_robot/src)
find_path(tron2_talky_INC tron2/talky/Talker.h  PATHS ${tron2_HOME}/tron2_talky/src)

find_library(tron2_robot_LIB tron2_robot  PATHS ${tron2_HOME}/tron2_robot/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(tron2_talky_LIB tron2_talky  PATHS ${tron2_HOME}/tron2_talky/dist  PATH_SUFFIXES ${TARGET_SYSTEM})

# ALL TOGETHER ...
# set(module_LIBRARIES     ${x_LIB} ${y_LIB} ...)
# set(module_INCLUDE_DIRS     ${x_INC} ${y_INC} ...)
set(tron2_LIBRARIES      ${tron2_robot_LIB} ${tron2_talky_LIB})
set(tron2_INCLUDE_DIRS   ${tron2_robot_INC} ${tron2_talky_INC})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set module_FOUND to TRUE if all listed variables are TRUE
find_package_handle_standard_args(amy DEFAULT_MSG tron2_robot_INC tron2_talky_INC tron2_robot_LIB tron2_talky_LIB)

mark_as_advanced(tron2_robot_INC tron2_talky_INC tron2_robot_LIB tron2_talky_LIB)



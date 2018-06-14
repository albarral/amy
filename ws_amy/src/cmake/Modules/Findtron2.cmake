# Files finder for tron2 libraries
# This finder obtains the following variables:
#  tron2_FOUND - System has the package
#  tron2_INCLUDE_DIRS - The include directories
#  tron2_LIBRARIES - The libraries needed

# required tron2 libs: 
# - tron2_robot   (libtron2_robot.so)
# - tron2_coms  (libtron2_coms.so)

set (tron2_HOME /home/albarral/DEV/tron2)
set (TARGET_SYSTEM Debug/GNU-Linux)

find_path(tron2_robot_INC tron2/robot/RobotSystem.h  PATHS ${tron2_HOME}/tron2_robot/src)
find_path(tron2_coms_INC tron2/coms/ChannelCommunicator.h  PATHS ${tron2_HOME}/tron2_coms/src)

find_library(tron2_robot_LIB tron2_robot  PATHS ${tron2_HOME}/tron2_robot/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(tron2_coms_LIB tron2_coms  PATHS ${tron2_HOME}/tron2_coms/dist  PATH_SUFFIXES ${TARGET_SYSTEM})

# ALL TOGETHER ...
# set(module_LIBRARIES     ${x_LIB} ${y_LIB} ...)
# set(module_INCLUDE_DIRS     ${x_INC} ${y_INC} ...)
set(tron2_LIBRARIES      ${tron2_robot_LIB} ${tron2_coms_LIB})
set(tron2_INCLUDE_DIRS   ${tron2_robot_INC} ${tron2_coms_INC})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set module_FOUND to TRUE if all listed variables are TRUE
find_package_handle_standard_args(tron2 DEFAULT_MSG tron2_robot_INC tron2_coms_INC tron2_robot_LIB tron2_coms_LIB)

mark_as_advanced(tron2_robot_INC tron2_coms_INC tron2_robot_LIB tron2_coms_LIB)



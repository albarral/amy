# - Try to find tron libs (for robotic coms)
# Once done this will define
#  tron_FOUND - System has the package
#  tron_INCLUDE_DIRS - The include directories
#  tron_LIBRARIES - The libraries needed

# required modules from tron package: 
# - tron_robot 	(libtron_robot.so)
# - tron_talky2  (libtron_talky2.so)
# - tron_tuly   (libtron_tuly.so)
# - tron_wire   (libtron_wire.so)
# - tron_wire2  (libtron_wire2.so)

set (TRON_HOME /home/albarral/DEV/tron)
set (TARGET_SYSTEM Debug/GNU-Linux)

find_path(tron_robot_INC tron/robot/RobotNodes.h  PATHS ${TRON_HOME}/robot/src)
find_path(tron_talky2_INC tron/talky2/Talker.h  PATHS ${TRON_HOME}/talky2/src)
find_path(tron_tuly_INC  tuly/utils/FileReader.h  PATHS ${TRON_HOME}/tuly/src)
find_path(tron_wire_INC  tron/wire/Wire.h  PATHS ${TRON_HOME}/wire/src)
find_path(tron_wire2_INC  tron/wire2/FileWire.h  PATHS ${TRON_HOME}/wire2/src)

find_library(tron_robot_LIB tron_robot  PATHS ${TRON_HOME}/robot/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(tron_talky2_LIB tron_talky2  PATHS ${TRON_HOME}/talky2/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(tron_tuly_LIB  tron_tuly  PATHS ${TRON_HOME}/tuly/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(tron_wire_LIB  tron_wire  PATHS ${TRON_HOME}/wire/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(tron_wire2_LIB tron_wire2 PATHS ${TRON_HOME}/wire2/dist  PATH_SUFFIXES ${TARGET_SYSTEM})

# ALL TOGETHER ...
# set(module_LIBRARIES     ${x_LIB} ${y_LIB} ...)
# set(module_INCLUDE_DIRS     ${x_INC} ${y_INC} ...)
set(tron_LIBRARIES      ${tron_robot_LIB} ${tron_talky2_LIB} ${tron_tuly_LIB} ${tron_wire_LIB} ${tron_wire2_LIB})
set(tron_INCLUDE_DIRS   ${tron_robot_INC} ${tron_talky2_INC} ${tron_tuly_INC} ${tron_wire_INC} ${tron_wire2_INC})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set module_FOUND to TRUE if all listed variables are TRUE
find_package_handle_standard_args(amy DEFAULT_MSG tron_robot_INC tron_talky2_INC tron_tuly_INC tron_wire_INC tron_wire2_INC tron_robot_LIB tron_talky2_LIB tron_tuly_LIB tron_wire_LIB tron_wire2_LIB)

mark_as_advanced(tron_robot_INC tron_talky2_INC tron_tuly_INC tron_wire_INC tron_wire2_INC tron_robot_LIB tron_talky2_LIB tron_tuly_LIB tron_wire_LIB tron_wire2_LIB)



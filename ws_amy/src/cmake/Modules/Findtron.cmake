# - Try to find tron libs (for robotic coms)
# Once done this will define
#  tron_FOUND - System has the package
#  tron_INCLUDE_DIRS - The include directories
#  tron_LIBRARIES - The libraries needed

# required modules from tron package: 
# - tron_talky  (libtron_talky.so)
# - tron_tuly   (libtron_tuly.so)
# - tron_comy 	(libtron_comy.so)

set (TRON_HOME /home/albarral/DEV/tron)
set (TARGET_SYSTEM Debug/GNU-Linux)

find_path(tron_talky_INC talky/Topics.h  PATHS ${TRON_HOME}/talky/src)
find_path(tron_tuly_INC  tuly/utils/File.h  PATHS ${TRON_HOME}/tuly/src)
find_path(tron_comy_INC  comy/ComyClient.h  PATHS ${TRON_HOME}/comy/src)

find_library(tron_talky_LIB tron_talky  PATHS ${TRON_HOME}/talky/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(tron_tuly_LIB  tron_tuly  PATHS ${TRON_HOME}/tuly/dist  PATH_SUFFIXES ${TARGET_SYSTEM})
find_library(tron_comy_LIB  tron_comy  PATHS ${TRON_HOME}/comy/dist  PATH_SUFFIXES ${TARGET_SYSTEM})

# ALL TOGETHER ...
# set(module_LIBRARIES     ${x_LIB} ${y_LIB} ...)
# set(module_INCLUDE_DIRS     ${x_INC} ${y_INC} ...)
set(tron_LIBRARIES      ${tron_talky_LIB} ${tron_tuly_LIB} ${tron_comy_LIB})
set(tron_INCLUDE_DIRS   ${tron_talky_INC} ${tron_tuly_INC} ${tron_comy_INC})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set module_FOUND to TRUE if all listed variables are TRUE
find_package_handle_standard_args(amy DEFAULT_MSG tron_talky_INC tron_tuly_INC tron_comy_INC tron_talky_LIB tron_tuly_LIB tron_comy_LIB)

mark_as_advanced(tron_talky_INC tron_tuly_INC tron_comy_INC tron_talky_LIB tron_tuly_LIB tron_comy_LIB)



# - Find ignition
# Find the ignition headers and libraries.
#
#  IGNITION_INCLUDE_DIRS   - Where to find ignition header files.
#  IGNITION_LIBRARIES      - List of libraries for using ignition.
#  IGNITION_FOUND          - True if ignition found.

# Look for the header files.
find_path(IG_TRANSPORT_DIR NAMES ignition/transport.hh PATH_SUFFIXES ignition/transport3)
mark_as_advanced(IG_TRANSPORT_DIR)
find_path(IG_MESSAGES_DIR NAMES ignition/msgs.hh PATH_SUFFIXES ignition/msgs0)
mark_as_advanced(IG_MESSAGES_DIR)
find_path(IG_MATHS_DIR NAMES ignition/math.hh PATH_SUFFIXES ignition/math2)
mark_as_advanced(IG_MATHS_DIR)

# Look for the libraries.
find_library(IG_LIBS NAMES
	ignition-transport3
	ignition-msgs0
	ignition-math2
)
mark_as_advanced(IG_LIBS)

# handle the QUIETLY and REQUIRED arguments and set IGNITION_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(IGNITION
                                  REQUIRED_VARS IG_TRANSPORT_DIR IG_MESSAGES_DIR IG_MATHS_DIR IG_LIBS)

if(IGNITION_FOUND)
  set(IGNITION_LIBRARIES ${IG_LIBS})
  set(IGNITION_INCLUDE_DIRS ${IG_TRANSPORT_DIR} ${IG_MESSAGES_DIR} ${IG_MATHS_DIR})
endif()



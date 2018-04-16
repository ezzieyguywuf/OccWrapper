# Try to find pybind11
# Once done, this will define:
# PYBIND11_FOUND - System has pybind11
# PYBIND11_INCLUDE_DIRS - The pybind11 include dirs
# PYBIND11_LIBRARIES - The libraries needed to build with pybind11

message("Searching for PYBIND11.....")
set(PYBIND11_FOUND "NO")

find_path(PYBIND11_INCLUDE_DIR "pybind11/pybind11.h"
    HINTS ${PROJECT_SOURCE_DIR}/../pybind11
    PATH_SUFFIXES include
)

set(PYBIND11_LIBRARY "/")

include(FindPackageHandleStandardArgs) # to handle standard args, provided by cMake (?)
find_package_handle_standard_args(pybind11 DEFAULT_MSG
                                  PYBIND11_INCLUDE_DIR PYBIND11_LIBRARY)

if (PYBIND11_FOUND)
    Message("-- Found pybind11")
    Message("-- -- pybind11 include dir = ${PYBIND11_INCLUDE_DIR}")
    Message("-- -- pybind11 library dir = n/a")
endif (PYBIND11_FOUND)

mark_as_advanced(PYBIND11_INCLUDE_DIR)
mark_as_advanced(PYBIND11_LIBRARY)
set(PYBIND11_INCLUDE_DIRS ${PYBIND11_INCLUDE_DIR})

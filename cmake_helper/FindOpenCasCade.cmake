# Try to find OPENCASCADE
# Once done, this will define:
# OPENCASCADE_FOUND - System has OpenCasCade
# OPENCASCADE_INCLUDE_DIRS - The OpenCasCade include directories
# OPENCASCADE_LIBRARIES - The libraries needed to use OpenCasCade

set (OPENCASCADE_FOUND "NO")

find_path(OPENCASCADE_INCLUDE_DIR TopoDS_Shape.hxx
    HINTS ${CMAKE_SOURCE_DIR}/../opencascade-7.0.0/
          ${CMAKE_SOURCE_DIR}/../opencascade-7.1.0/
          ${CMAKE_SOURCE_DIR}/../opencascade-7.2.0/
    PATH_SUFFIXES inc oce opencascade)

find_library(OPENCASCADE_LIBRARY 
    HINTS ${CMAKE_SOURCE_DIR}/../opencascade-7.0.0/build/lin64/gcc/lib
          ${CMAKE_SOURCE_DIR}/../opencascade-7.1.0/build/lin64/gcc/lib
          ${CMAKE_SOURCE_DIR}/../opencascade-7.2.0/build/lin64/gcc/lib
    NAMES TKBRep)

get_filename_component(OPENCASCADE_LIBRARIES_DIR ${OPENCASCADE_LIBRARY} DIRECTORY CACHE)

include(FindPackageHandleStandardArgs) # to handle standard args, provided by cMake (?)
find_package_handle_standard_args(OPENCASCADE DEFAULT_MSG
                                  OPENCASCADE_INCLUDE_DIR OPENCASCADE_LIBRARY)
if (OPENCASCADE_FOUND)
    message("-- Found OpenCasCade")
    message("-- -- OpenCasCade include directory = ${OPENCASCADE_INCLUDE_DIR}")
    message("-- -- OpenCasCade library directory = ${OPENCASCADE_LIBRARIES_DIR}")
endif(OPENCASCADE_FOUND)

mark_as_advanced(OPENCASCADE_INCLUDE_DIR OPENCASCADE_LIBRARY)
set(OPENCASCADE_INCLUDE_DIRS ${OPENCASCADE_INCLUDE_DIR} CACHE PATH "OCC include directory.")
set(OPENCASCADE_LIBRARIES 
    TKFillet
    TKernel
    TKG2d
    TKG3d
    TKMath 
    TKShHealing
    TKBool
    TKBO
    TKBRep 
    TKTopAlgo
    TKGeomAlgo
    TKGeomBase
    TKPrim
    TKFeat

    TKCAF
    TKLCAF
    )


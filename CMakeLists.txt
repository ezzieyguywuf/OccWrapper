cmake_minimum_required(VERSION 3.7)

project(OccWrapper)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_BUILD_TYPE "Debug")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wextra -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wall")

set (CMAKE_HELPER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake_helper")
set (BUILD_SHARED_LIBS OFF)

set(OCC_INCLUDE "/home/wolfie/Program/FreeCAD_dev/opencascade-7.1.0/inc")
set(OCC_LIBRARIES "/home/wolfie/Program/FreeCAD_dev/opencascade-7.1.0/build/lin64/gcc/libd")
set(OCC_LIBS 
    TKBRep 
    TKPrim
    TKernel
    TKGeomAlgo
    TKTopAlgo
    TKMath 
    TKBO
    TKG3d
    TKGeomBase
    TKCAF
    TKLCAF
    TKBool
    TKFillet
    #TKShHealing
    )

include_directories(
    "include"
    ${OCC_INCLUDE}
)

link_directories(
    ${OCC_LIBRARIES}
    )

add_subdirectory(src)

set(CTEST_ENVIRONMENT CTEST_OUTPUT_ON_FAILURE=1)
enable_testing()

add_subdirectory(test)

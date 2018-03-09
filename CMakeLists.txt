cmake_minimum_required(VERSION 3.7)

project(OccWrapper)

set (CMAKE_HELPER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake_helper")

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
#add_subdirectory(test)

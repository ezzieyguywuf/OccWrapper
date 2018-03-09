add_library(OccShape OccShape.cpp)
target_link_libraries(OccShape ${OCC_LIBS})

add_library(OccSolid OccSolid.cpp)
target_link_libraries(OccSolid ${OCC_LIBS} OccShape OccFace)

add_library(OccFace OccFace.cpp)
target_link_libraries(OccFace ${OCC_LIBS} OccShape)

add_library(OccShape OccShape.cpp)
target_link_libraries(OccShape ${OCC_LIBS})

add_library(OccSolid OccSolid.cpp)
target_link_libraries(OccSolid ${OCC_LIBS} OccShape OccFace)

add_library(OccFace OccFace.cpp)
target_link_libraries(OccFace ${OCC_LIBS} OccShape)

add_library(OccBox OccBox.cpp)
target_link_libraries(OccBox ${OCC_LIBS} OccSolid)

add_library(OccCylinder OccCylinder.cpp)
target_link_libraries(OccCylinder ${OCC_LIBS} OccSolid)

add_library(OccModifiedSolid OccModifiedSolid.cpp)
target_link_libraries(OccModifiedSolid OccSolid OccBox)

add_library(OccModifiedSolids OccModifiedSolids.cpp)
target_link_libraries(OccModifiedSolids OccModifiedSolid OccSolid)

add_library(OccSolidModifier OccSolidModifier.cpp)
target_link_libraries(OccSolidModifier ${OCC_LIBS} OccModifiedSolid)

add_library(OccSolidMaker OccSolidMaker.cpp)
target_link_libraries(OccSolidMaker ${OCC_LIBS} OccBox OccCylinder)

add_library(PrimitiveSolidManager PrimitiveSolidManager.cpp)
target_link_libraries(PrimitiveSolidManager OccSolid)

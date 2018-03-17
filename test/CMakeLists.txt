include(${CMAKE_HELPER_DIR}/functions.cmake)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

AddTest("OccEdgeTester" ${OCC_LIBS} OccEdge OccSolid OccSolidMaker)
AddTest("OccShapeTester" OccShape)
AddTest("OccSolidTester" OccSolid)
AddTest("OccModifiedSolidTester" ${OCC_LIBS} OccSolidMaker OccModifiedSolid)
AddTest("OccSolidModifierTester" OccSolidModifier OccSolidMaker OccBooleanSolid)
AddTest("OccBooleanSolidTester" OccSolidModifier OccSolidMaker OccBooleanSolid)
AddTest("OccFaceComparatorTester" ${OCC_LIBS} OccFaceComparator OccSolidMaker OccSolidModifier OccBooleanSolid)

add_executable("SimpleTest" "SimpleTest.cpp")
target_link_libraries("SimpleTest" ${OCC_LIBS} OccFaceComparator OccSolidMaker OccModifiedSolid OccSolidModifier OccBooleanSolid)

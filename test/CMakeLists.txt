
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

AddTest("OccEdgeTester" OccSolidMaker)
AddTest("OccShapeTester" OccBox)
AddTest("OccSolidTester" OccSolid)
AddTest("OccModifiedSolidTester" OccSolidMaker OccModifiedSolid)
AddTest("OccSolidModifierTester" OccSolidMaker OccSolidModifier)
AddTest("OccSolidMakerTester" OccSolidMaker OccSolidModifier)
AddTest("OccBooleanSolidTester" OccSolidModifier OccSolidMaker)
#AddTest("OccFaceComparatorTester" ${OPENCASCADE_LIBS} OccEdge OccFaceComparator OccSolidMaker OccSolidModifier OccBooleanSolid)

add_executable("SimpleTest" "SimpleTest.cpp")
target_link_libraries("SimpleTest" ${OPENCASCADE_LIBS} OccEdge OccSolidMaker OccModifiedSolid OccSolidModifier OccBooleanSolid)

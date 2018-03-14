include(${CMAKE_HELPER_DIR}/functions.cmake)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

AddTest("OccShapeTester" OccShape)
AddTest("OccSolidTester" OccSolid)
AddTest("OccSolidModifierTester" OccSolidModifier OccSolidMaker OccBooleanSolid)

add_executable("SimpleTest" "SimpleTest.cpp")
target_link_libraries("SimpleTest" ${OCC_LIBS} OccSolidMaker OccSolidModifier OccBooleanSolid)

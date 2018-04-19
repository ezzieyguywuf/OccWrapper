cmake_minimum_required(VERSION 3.7)

project(OccWrapper)

add_subdirectory(pybind11)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_BUILD_TYPE "Debug")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wextra -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wextra -Wall")

set (CMAKE_HELPER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake_helper")
set (CMAKE_MODULE_PATH ${CMAKE_HELPER_DIR})
include(${CMAKE_HELPER_DIR}/functions.cmake)
#set (BUILD_SHARED_LIBS ON)

find_package(OpenCasCade REQUIRED)
include_directories(
    "include"
    ${OPENCASCADE_INCLUDE_DIRS}
)

link_directories(
    ${OPENCASCADE_LIBRARIES_DIR}
)

add_subdirectory(src)
add_subdirectory(srcPy)

set(CTEST_ENVIRONMENT CTEST_OUTPUT_ON_FAILURE=1)
enable_testing()

add_subdirectory(test)


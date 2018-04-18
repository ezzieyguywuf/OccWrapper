function(AddTest SrcName)
    add_executable(${SrcName} "${SrcName}.cpp")
    target_link_libraries(${SrcName} "gtest_main" ${ARGN})
    add_test(NAME "TEST_${SrcName}" COMMAND $<TARGET_FILE:${SrcName}>)
endfunction(AddTest)

function(AddLib SrcName)
    if ((${ARGC} GREATER 1) AND (NOT ${ARGV1} STREQUAL "STATIC") OR (${ARGC} EQUAL 1))
        add_library(${SrcName} "${SrcName}.cpp")
        target_link_libraries(${SrcName} ${ARGN})
    elseif(${ARGC} GREATER 1)
        add_library(${SrcName} STATIC "${SrcName}.cpp")
        list(REMOVE_AT ARGN 0)
        target_link_libraries(${SrcName} ${ARGN})
    else()
        message(FATAL_ERROR "This line should not execute...")
    endif()
endfunction(AddLib)

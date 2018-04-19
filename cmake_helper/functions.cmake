function(AddTest SrcName)
    add_executable(${SrcName} "${SrcName}.cpp")
    target_link_libraries(${SrcName} "gtest_main" ${ARGN})
    add_test(NAME "TEST_${SrcName}" COMMAND $<TARGET_FILE:${SrcName}>)
endfunction(AddTest)

function(AddLib SrcName)
    add_library(${SrcName} SHARED "${SrcName}.cpp")
    target_link_libraries(${SrcName} ${ARGN})
    set_target_properties(${SrcName} PROPERTIES PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/include/${SrcName}.h")

    install(TARGETS ${SrcName}
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib/static"
        PRIVATE_HEADER DESTINATION "include"
        PUBLIC_HEADER DESTINATION "include"
    )
endfunction(AddLib)

function(AddPyLib SrcName)
    add_library(${SrcName} STATIC "${SrcName}.cpp")
    target_link_libraries(${SrcName} ${ARGN})
endfunction(AddPyLib)

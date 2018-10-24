cmake_minimum_required(VERSION 3.10)




project(pmcpp)

if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
    endif ()
else ()
    set (CMAKE_CXX_STANDARD 11)
endif ()
add_definitions("-Wno-c++11-extensions")
add_definitions("-Wno-parentheses")


add_subdirectory(lib/cppzmq)
#add_subdirectory(lib/pureparameters)
#include_directories(lib/pureparameters/include)
#add_library(PM src/PureMessage.cpp include/PureMessage.hpp)


add_executable(
        main
#        lib/pureparameters/pureparameter.h
        #src/PureMessage.cpp
        test/main.cpp
        )
#######################
# preprocessor macro definitions



#############
# link
target_link_libraries(
        main
        cppzmq
        #PM

)
#
#add_test(
#        NAME
#        tst
#        COMMAND
#        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/cpp
#)





project(master-preproc)
cmake_minimum_required(VERSION 2.8.9)

add_definitions(-std=c++11 -std=gnu++11 -pthread -W -Wall -Wno-unused-function)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_VERBOSE_MAKEFILE ON)
else()
    add_definitions(-Ofast)
endif()

add_executable(master-preproc spellchecker.cpp main.cpp)

target_link_libraries(master-preproc aspell)

install(TARGETS master-preproc RUNTIME DESTINATION bin)

add_subdirectory(tests)

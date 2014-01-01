project(master-preproc)

add_definitions(-std=c++11 -std=gnu++11 -pthread -W -Wall -Wno-unused-function)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_VERBOSE_MAKEFILE ON)
else()
    add_definitions(-Ofast)
endif()

add_executable(master-preproc main.cpp)

install(TARGETS master-preproc RUNTIME DESTINATION bin)

add_subdirectory(tests)
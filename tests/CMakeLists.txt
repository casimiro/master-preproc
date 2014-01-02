find_library(LIBPTHREAD NAMES pthread)

include_directories($ENV{GMOCK_HOME}/include $ENV{GMOCK_HOME}/gtest/include ../ ${SOCI_INCLUDE_DIRS})

link_directories($ENV{GMOCK_HOME}/build $ENV{GMOCK_HOME}/gtest/build)

add_executable(tests main.cpp testcleantexts.cpp delafdicttests.cpp spelltests.cpp ../delafdict.cpp ../utils.cpp ../spellchecker.cpp)

enable_testing()

target_link_libraries(tests gmock gtest ${LIBPTHREAD} icuuc icudata icui18n aspell)

add_test(
    NAME tests
    COMMAND tests
)

add_custom_command(TARGET tests COMMAND cp -r ${CMAKE_SOURCE_DIR}/tests/fixtures ${CMAKE_BINARY_DIR}/tests)

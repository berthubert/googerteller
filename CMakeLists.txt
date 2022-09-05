cmake_minimum_required(VERSION 3.1)

project(googerteller VERSION 1.0
                  DESCRIPTION "Audible feedback on Google communications"
                  LANGUAGES CXX C)


set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_custom_target(Work ALL DEPENDS configs.hh)


add_executable(teller teller.cc ext/lpm.c)
target_link_libraries(teller -lpcaudio -lpthread)

add_executable(testrunner testrunner.cc ext/lpm.c )
target_link_libraries(testrunner -lpcaudio)

enable_testing()
add_test(testname testrunner)

add_custom_command(
    OUTPUT   configs.hh
    COMMAND  ./make-built-in-config.sh
    DEPENDS  teller.conf trackers.conf
)


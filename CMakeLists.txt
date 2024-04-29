cmake_minimum_required(VERSION 3.1)

project(googerteller VERSION 1.0
                  DESCRIPTION "Audible feedback on Google communications"
                  LANGUAGES CXX C)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

message("-- Looking for Portable C Audio Library")
find_library(PCAUDIO_LIB NAMES pcaudio libpcaudio)
if (NOT PCAUDIO_LIB)
    message(FATAL_ERROR "Could not find PCAUDIO_LIB using the following names: pcaudio, libpcaudio")
endif()
message("-- Looking for Portable C Audio Library - found")

add_custom_target(Work ALL DEPENDS configs.hh)

add_executable(teller teller.cc ext/lpm.c)
target_link_libraries(teller PRIVATE ${PCAUDIO_LIB} Threads::Threads)

add_executable(testrunner testrunner.cc ext/lpm.c )
target_link_libraries(testrunner PRIVATE ${PCAUDIO_LIB})

enable_testing()
add_test(testname testrunner)

add_custom_command(
    OUTPUT   configs.hh
    COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/make-built-in-config.sh ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS  teller.conf trackers.conf
)


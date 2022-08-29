cmake_minimum_required(VERSION 3.1)

project(googerteller VERSION 1.0
                  DESCRIPTION "Audible feedback on Google communications"
                  LANGUAGES CXX C)


set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

#add_library(support STATIC ext/powerblog/h2o-pp.cc 
#	ext/powerblog/ext/simplesocket/swrappers.cc 
#	ext/powerblog/ext/simplesocket/comboaddress.cc 
#	ext/powerblog/ext/simplesocket/sclasses.cc 
#	ext/fmt-7.1.3/src/format.cc)



#target_include_directories(support PUBLIC ext/powerblog/ext/simplesocket ext/powerblog/ext ext/fmt-7.1.3/include/)
#target_link_libraries(support PUBLIC -lh2o-evloop -lssl -lcrypto Threads::Threads)

add_executable(teller teller.cc ext/lpm.c)
target_link_libraries(teller -lpcaudio -lpthread)

add_executable(testrunner testrunner.cc ext/lpm.c )
target_link_libraries(testrunner -lpcaudio)

enable_testing()
add_test(testname testrunner)


enable_testing()
add_test(testname testrunner)

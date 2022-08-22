cmake_minimum_required(VERSION 3.1)

project(googerteller VERSION 1.0
                  DESCRIPTION "Audible feedback on Google communications"
                  LANGUAGES CXX)


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

add_library(pcaudiolib SHARED IMPORTED)
add_executable(teller teller.cc )
if (APPLE)
  set_target_properties(pcaudiolib PROPERTIES
    IMPORTED_LOCATION "/usr/local/lib/libpcaudio.dylib"
    INTERFACE_INCLUDE_DIRECTORIES "/usr/local/include"
  )
  target_include_directories(teller PUBLIC /usr/local/include/)
else()
  set_target_properties(pcaudiolib PROPERTIES
    IMPORTED_LOCATION "/usr/local/lib/libpcaudio.so"
  )  
endif()
target_link_libraries(teller pcaudiolib -lpthread)

#enable_testing()
#add_test(testname testrunner)

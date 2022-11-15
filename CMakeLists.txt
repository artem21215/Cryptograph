cmake_minimum_required(VERSION 3.17)
project(TheoryProgrammingLanguage)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)

#Add the google test subdirectory
#add_subdirectory(./ C://)

#include googletest/include dir
include_directories(C:/googletest/include)

#include the googlemock/include dir
include_directories(C:/googlemock/include)

add_executable(TheoryProgrammingLanguage main.cpp modulArithmetics.cpp modulArithmetics.h Speakers.cpp Speakers.h Crypt.cpp Crypt.h LongArithmetic.cpp LongArithmetic.h Signs.cpp Signs.h)
target_link_libraries(TheoryProgrammingLanguage OpenSSL::SSL)

#Link with GoogleTest
target_link_libraries(TheoryProgrammingLanguage gtest gtest_main)

#Link with GoogleMock
target_link_libraries(TheoryProgrammingLanguage gmock gmock_main)
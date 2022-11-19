cmake_minimum_required(VERSION 3.17)
project(CryptographGlobal)

set(CMAKE_CXX_STANDARD 11)

set (SOURCE_FILES main.cpp)
add_executable(cryptograph_samples ${SOURCE_FILES})

include_directories(Cryptograph)

add_subdirectory(Cryptograph)
add_subdirectory(CryptographTests)

target_link_libraries(cryptograph_samples Cryptograph)
cmake_minimum_required(VERSION 3.17)
project(CryptographProject)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenSSL REQUIRED)

#add_executable(Cryptograph main.cpp modulArithmetics.cpp modulArithmetics.h Speakers.cpp Speakers.h Crypt.cpp Crypt.h LongArithmetic.cpp LongArithmetic.h Signs.cpp Signs.h)
add_library(Cryptograph modulArithmetics.cpp modulArithmetics.h Speakers.cpp Speakers.h Crypt.cpp Crypt.h LongArithmetic.cpp LongArithmetic.h Signs.cpp Signs.h Pocker.cpp Pocker.h)
target_link_libraries(Cryptograph OpenSSL::SSL)
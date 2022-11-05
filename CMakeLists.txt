cmake_minimum_required(VERSION 3.17)
project(TheoryProgrammingLanguage)

set(CMAKE_CXX_STANDARD 17)

add_executable(TheoryProgrammingLanguage main.cpp modulArithmetics.cpp modulArithmetics.h Speakers.cpp Speakers.h Crypt.cpp Crypt.h LongArithmetic.cpp LongArithmetic.h)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runCommonTests LongArithmeticTests.cpp ModulArithmeticTests.cpp)

target_link_libraries(runCommonTests gtest gtest_main)
target_link_libraries(runCommonTests Cryptograph)

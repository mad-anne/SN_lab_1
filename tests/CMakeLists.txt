cmake_minimum_required(VERSION 3.7)
project(tests)

add_subdirectory(lib/googletest)

enable_testing()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES
        gtest.cpp

        tests/classifiers/PerceptronTestSuite.cpp

        tests/datasets/DataTestSuite.cpp
        tests/datasets/DataSetTestSuite.cpp
        tests/datasets/DataSetAccessorTestSuite.cpp

        tests/functions/BipolarStepFunctionTestSuite.cpp
        tests/functions/UnipolarStepFunctionTestSuite.cpp

        tests/neurons/NeuronTestSuite.cpp)

add_executable(tests_run ${SOURCE_FILES})

target_link_libraries(tests_run gtest gtest_main sourcelib)
cmake_minimum_required(VERSION 3.7)
project(src)

set(SOURCE_FILES
        perceptron/source/Perceptron.cpp)

add_library (sourcelib ${SOURCE_FILES})

add_executable(sn_lab_1_run ../main.cpp)

target_link_libraries(sn_lab_1_run sourcelib)
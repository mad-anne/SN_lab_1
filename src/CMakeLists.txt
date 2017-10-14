cmake_minimum_required(VERSION 3.7)
project(src)

set(SOURCE_FILES
        classifiers/source/Adaline.cpp
        classifiers/source/Perceptron.cpp

        datasets/source/Data.cpp
        datasets/source/DataSet.cpp
        datasets/source/DataSetAccessor.cpp

        files/source/DataSetReader.cpp
        files/source/ParametersReader.cpp

        functions/source/BipolarStepFunction.cpp
        functions/source/UnipolarStepFunction.cpp

        neurons/source/Neuron.cpp)

add_library (sourcelib ${SOURCE_FILES})

add_executable(sn_lab_1_run ../main.cpp)

target_link_libraries(sn_lab_1_run sourcelib)
#include <iostream>
#include <vector>

#include "classifiers/header/Perceptron.h"
#include "datasets/header/Data.h"
#include "datasets/header/DataSet.h"
#include "datasets/header/DataSetAccessor.h"
#include "functions/header/UnipolarStepFunction.h"
#include "neurons/header/Neuron.h"


const size_t DATA_SET_SIZE = 4;
const size_t DATA_SIZE = 2;

std::vector<const IData*>* getDataSet();

int main()
{
    const IDataSet* dataSet = new DataSet(getDataSet(), DATA_SIZE, DATA_SET_SIZE);
    IDataSetAccessor* dataSetAccessor = new DataSetAccessor(dataSet);
    Perceptron perceptron(0.01, dataSetAccessor, new Neuron(new UnipolarStepFunction(0.5)));

    std::cout << "Perceptron starts to learn..." << std::endl;
    perceptron.learn(100);
    std::cout << "Perceptron finished learning." << std::endl;

    const IData* input = new Data(new double[DATA_SIZE] {0, 0}, new int(0), DATA_SIZE);
    std::cout << "Perceptron predict 0 and 0" << std::endl;
    std::cout << perceptron.predict(input) << std::endl << std::endl;
    delete input;

    input = new Data(new double[DATA_SIZE] {0, 1}, new int(0), DATA_SIZE);
    std::cout << "Perceptron predict 0 and 1" << std::endl;
    std::cout << perceptron.predict(input) << std::endl << std::endl;
    delete input;

    input = new Data(new double[DATA_SIZE] {1, 0}, new int(0), DATA_SIZE);
    std::cout << "Perceptron predict 1 and 0" << std::endl;
    std::cout << perceptron.predict(input) << std::endl << std::endl;
    delete input;

    input = new Data(new double[DATA_SIZE] {1, 1}, new int(1), DATA_SIZE);
    std::cout << "Perceptron predict 1 and 1" << std::endl;
    std::cout << perceptron.predict(input) << std::endl << std::endl;
    delete input;

    delete dataSet;
    return 0;
}

std::vector<const IData*>* getDataSet()
{
    auto * _dataSet = new std::vector<const IData*>();
    (*_dataSet).push_back(new Data(new double[DATA_SIZE] {0, 0}, new int(0), DATA_SIZE));
    (*_dataSet).push_back(new Data(new double[DATA_SIZE] {0, 1}, new int(0), DATA_SIZE));
    (*_dataSet).push_back(new Data(new double[DATA_SIZE] {1, 0}, new int(0), DATA_SIZE));
    (*_dataSet).push_back(new Data(new double[DATA_SIZE] {1, 1}, new int(1), DATA_SIZE));
    return _dataSet;
}
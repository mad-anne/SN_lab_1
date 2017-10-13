#include <iostream>
#include <vector>

#include "classifiers/header/Perceptron.h"
#include "datasets/header/Data.h"
#include "datasets/header/DataSetAccessor.h"
#include "files/header/DataSetReader.h"
#include "files/header/ParametersReader.h"
#include "functions/header/UnipolarStepFunction.h"
#include "neurons/header/Neuron.h"


const size_t DATA_SET_SIZE = 4;
const size_t DATA_SIZE = 2;

void process(const IDataSet* dataSet);

int main()
{
    IParametersReader* parametersReader = new ParametersReader();

    std::cout << "Reading parameters...\n\n";
    parametersReader->read();

    std::cout << "Parameters:\n";
    parametersReader->printParameters();

    size_t dataSize = (size_t) parametersReader->getParameter("dataSize");
    IDataSetReader* dataSetReader = new DataSetReader();

    std::cout << "\nReading dataset for AND...\n\n";
    const IDataSet* dataSet = dataSetReader->readDataSet("../../dataset_and.txt", dataSize);

    process(dataSet);

    delete dataSet;
    delete dataSetReader;
    delete parametersReader;

    return 0;
}

void process(const IDataSet* dataSet)
{
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
}
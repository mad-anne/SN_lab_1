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

void process(const IDataSet*, const IParametersReader*);
const IParametersReader* readParameters(const std::string& fileName);
const IDataSet* readDataSet(const IDataSetReader*, const IParametersReader*, const std::string& fileName);
const IDataSet* enlargeDataSet(const IDataSet*, const IParametersReader*);
const double* createDataWithDeviation(const double* srcData, const size_t dataSize, double deviation);

int main()
{
    const IParametersReader* parametersReader = readParameters("../../parameters.txt");
    const IDataSetReader* dataSetReader = new DataSetReader();
    const IDataSet* dataSet = readDataSet(dataSetReader, parametersReader, "../../dataset_and.txt");
    const IDataSet* enlargedDataSet = enlargeDataSet(dataSet, parametersReader);

    process(dataSet, parametersReader);

    delete enlargedDataSet;
    delete dataSet;
    delete dataSetReader;
    delete parametersReader;

    return 0;
}

const IDataSet* enlargeDataSet(const IDataSet* dataSet, const IParametersReader* parametersReader)
{
    int enlargeTimes = (int) parametersReader->getParameter("enlargeDataSetTimes");
    double deviation = parametersReader->getParameter("enlargedDataSetMaxDeviation");
    const size_t dataSize = dataSet->getDataSize();
    const size_t dataSetSize = dataSet->getDataSetSize();

    auto* _dataSet = new std::vector<const IData*>();

    for (int index = 0; index < dataSetSize; ++index)
    {
        const IData* data = dataSet->getData(index);
        const int* label = data->getLabel();
        const double* _data = data->getData();

        for (int time = 0; time < enlargeTimes; ++time)
        {
            const double* newData = createDataWithDeviation(_data, dataSize, deviation);
            _dataSet->push_back(new Data(newData, new int(*label), dataSize));
        }
    }
    return new DataSet(_dataSet, dataSize, dataSetSize * enlargeTimes);
}

const double* createDataWithDeviation(const double* srcData, const size_t dataSize, double deviation)
{
    auto* destData = new double[dataSize];
    for (int i = 0; i < dataSize; ++i)
    {
        double random = ((double) rand() / (double) RAND_MAX);
        destData[i] = srcData[i] + (2 * deviation * random - deviation);
    }
    return destData;
}

const IParametersReader* readParameters(const std::string& fileName)
{
    IParametersReader* parametersReader = new ParametersReader();

    std::cout << "Reading parameters from " << fileName << "...\n\n";
    parametersReader->read(fileName);

    std::cout << "Parameters:\n";
    parametersReader->printParameters();

    return parametersReader;
}

const IDataSet* readDataSet(
    const IDataSetReader* dataSetReader,
    const IParametersReader* parametersReader,
    const std::string& fileName)
{
    size_t dataSize = (size_t) parametersReader->getParameter("dataSize");

    std::cout << "\nReading dataset for AND from " << fileName << "...\n\n";
    const IDataSet* dataSet = dataSetReader->readDataSet(fileName, dataSize);
    std::cout << "Data set reading finished.\n\n";
    return dataSet;
}

void process(const IDataSet* dataSet, const IParametersReader* parametersReader)
{
    double alpha = parametersReader->getParameter("alpha");
    double theta = parametersReader->getParameter("theta");
    int epochs = (int) parametersReader->getParameter("epochs");
    double zeroDeviation = parametersReader->getParameter("randomWeightsZeroDeviation");

    IDataSetAccessor* dataSetAccessor = new DataSetAccessor(dataSet);
    Perceptron perceptron(alpha, dataSetAccessor, new Neuron(new UnipolarStepFunction(theta)));

    std::cout << "Perceptron starts to learn..." << std::endl;
    perceptron.learn(epochs, zeroDeviation);
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

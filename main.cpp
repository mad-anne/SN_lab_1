#include <iostream>
#include <vector>

#include "classifiers/header/Adaline.h"
#include "classifiers/header/Perceptron.h"
#include "datasets/header/Data.h"
#include "datasets/header/DataSetAccessor.h"
#include "files/header/DataSetReader.h"
#include "files/header/ParametersReader.h"
#include "functions/header/BipolarStepFunction.h"
#include "functions/header/UnipolarStepFunction.h"
#include "neurons/header/Neuron.h"


const size_t DATA_SET_SIZE = 4;
const size_t DATA_SIZE = 2;

void process(IDataSetAccessor*, const IParametersReader*);
void processAdaline(IDataSetAccessor*, const IParametersReader*);

const IParametersReader* readParameters(const std::string& fileName);
const IDataSet* readDataSet(const IDataSetReader*, const IParametersReader*, const std::string& fileName);

const IDataSet* enlargeDataSet(const IDataSet*, const IParametersReader*);
const double* createDataWithDeviation(const double* srcData, const size_t dataSize, double deviation);

IDataSetAccessor* prepareDataSetWithAccessor(const IDataSet*, const IParametersReader*);
void predict(IClassifier* classifier, double value1, double value2, int label);

int main()
{
    const IParametersReader* parametersReader = readParameters("../../parameters.txt");
    const IDataSetReader* dataSetReader = new DataSetReader();
    const IDataSet* dataSet = readDataSet(dataSetReader, parametersReader, "../../dataset_and_unipolar.txt");
    const IDataSet* enlargedDataSet = enlargeDataSet(dataSet, parametersReader);
    IDataSetAccessor* dataSetAccessor = prepareDataSetWithAccessor(enlargedDataSet, parametersReader);

    process(dataSetAccessor, parametersReader);
    processAdaline(dataSetAccessor, parametersReader);

    delete dataSetAccessor;
    delete enlargedDataSet;
    delete dataSet;
    delete dataSetReader;
    delete parametersReader;

    return 0;
}

IDataSetAccessor* prepareDataSetWithAccessor(const IDataSet* dataSet, const IParametersReader* parametersReader)
{
    IDataSetAccessor* dataSetAccessor = new DataSetAccessor(dataSet);

    double trainingSetPart = parametersReader->getParameter("trainingSetPart");
    double validatingSetPart = parametersReader->getParameter("validatingSetPart");
    double testingSetPart = parametersReader->getParameter("testingSetPart");

    dataSetAccessor->splitDataSet(trainingSetPart, validatingSetPart, testingSetPart);

    return dataSetAccessor;
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

    std::cout << "Reading parameters  finished\n\n";

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
    std::cout << "Reading dataset finished\n\n";
    return dataSet;
}

void process(IDataSetAccessor* dataSetAccessor, const IParametersReader* parametersReader)
{
    double alpha = parametersReader->getParameter("alpha");
    int epochs = (int) parametersReader->getParameter("epochs");
    double zeroDeviation = parametersReader->getParameter("randomWeightsZeroDeviation");
    double bias = parametersReader->getParameter("bias");

    IClassifier* perceptron = new Perceptron(alpha, new double(bias), dataSetAccessor, new Neuron(), new UnipolarStepFunction());

    std::cout << "Perceptron initializing random weights..." << std::endl;
    perceptron->initRandomWeights(zeroDeviation);
    std::cout << "Perceptron learning..." << std::endl;
    perceptron->learn(epochs);
    std::cout << "Perceptron finished learning" << std::endl;

    std::cout << "Perceptron with alpha = " << alpha << " and Unipolar step function predicts AND:\n";
    predict(perceptron, 0, 0, 0);
    predict(perceptron, 0, 1, 0);
    predict(perceptron, 1, 0, 0);
    predict(perceptron, 1, 1, 1);

    delete perceptron;
}

void processAdaline(IDataSetAccessor* dataSetAccessor, const IParametersReader* parametersReader)
{
    double alpha = parametersReader->getParameter("alpha");
    int epochs = (int) parametersReader->getParameter("epochs");
    double zeroDeviation = parametersReader->getParameter("randomWeightsZeroDeviation");
    double bias = parametersReader->getParameter("bias");
    double minMSE = parametersReader->getParameter("minMSE");

    IClassifier* adaline = new Adaline(alpha, new double(bias), minMSE, dataSetAccessor, new Neuron(), new BipolarStepFunction());

    std::cout << "Adaline initializing random weights..." << std::endl;
    adaline->initRandomWeights(zeroDeviation);
    std::cout << "Adaline learning AND..." << std::endl;
    adaline->learn(epochs);
    std::cout << "Adaline finished learning" << std::endl;

    std::cout << "Adaline with alpha = " << alpha << " and Bipolar step function predicts AND:\n";
    predict(adaline, -1, -1, -1);
    predict(adaline, -1, 1, -1);
    predict(adaline, 1, -1, -1);
    predict(adaline, 1, 1, 1);

    delete adaline;
}

void predict(IClassifier* classifier, double value1, double value2, int label)
{
    const IData* input = new Data(new double[DATA_SIZE] {value1, value2}, new int(label), DATA_SIZE);
    std::cout << "(" << value1 << ", " << value2 << ") = " << classifier->predict(input) << std::endl;
    delete input;
}
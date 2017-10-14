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


void processBipolarAnd(const IDataSetReader*, const IParametersReader*, double alpha, int epochs, double zeroDeviation, double bias, double minMSE);
void processUnipolarAnd(const IDataSetReader*, const IParametersReader*, double alpha, int epochs, double zeroDeviation, double bias, double minMSE);
void processBipolarOr(const IDataSetReader*, const IParametersReader*, double alpha, int epochs, double zeroDeviation, double bias, double minMSE);
void processUnipolarOr(const IDataSetReader*, const IParametersReader*, double alpha, int epochs, double zeroDeviation, double bias, double minMSE);

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

    double alpha = parametersReader->getParameter("alpha");
    int epochs = (int) parametersReader->getParameter("epochs");
    double zeroDeviation = parametersReader->getParameter("randomWeightsZeroDeviation");
    double bias = parametersReader->getParameter("bias");
    double minMSE = parametersReader->getParameter("minMSE");

    processUnipolarAnd(dataSetReader, parametersReader, alpha, epochs, zeroDeviation, bias, minMSE);
    processBipolarAnd(dataSetReader, parametersReader, alpha, epochs, zeroDeviation, bias, minMSE);
    processUnipolarOr(dataSetReader, parametersReader, alpha, epochs, zeroDeviation, bias, minMSE);
    processBipolarOr(dataSetReader, parametersReader, alpha, epochs, zeroDeviation, bias, minMSE);

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

    return parametersReader;
}

const IDataSet* readDataSet(
    const IDataSetReader* dataSetReader,
    const IParametersReader* parametersReader,
    const std::string& fileName)
{
    size_t dataSize = (size_t) parametersReader->getParameter("dataSize");

    std::cout << "\nReading dataset from " << fileName << "...\n\n";
    return dataSetReader->readDataSet(fileName, dataSize);
}

void processUnipolarAnd(
    const IDataSetReader* dataSetReader,
    const IParametersReader* parametersReader,
    double alpha,
    int epochs,
    double zeroDeviation,
    double bias,
    double minMSE)
{
    std::cout << "\nLearning classifiers for AND with Unipolar step function\n";

    const IDataSet* dataSet = readDataSet(dataSetReader, parametersReader, "../../dataset_and_unipolar.txt");
    const IDataSet* enlargedDataSet = enlargeDataSet(dataSet, parametersReader);
    IDataSetAccessor* dataSetAccessor = prepareDataSetWithAccessor(enlargedDataSet, parametersReader);

    IClassifier* perceptron = new Perceptron(alpha, new double(bias), dataSetAccessor, new Neuron(), new UnipolarStepFunction());
    std::cout << "Perceptron..." << std::endl;
    perceptron->initRandomWeights(zeroDeviation);
    perceptron->learn(epochs);

    predict(perceptron, 0, 0, 0);
    predict(perceptron, 0, 1, 0);
    predict(perceptron, 1, 0, 0);
    predict(perceptron, 1, 1, 1);

    delete perceptron;

    IClassifier* adaline = new Adaline(alpha, new double(bias), minMSE, dataSetAccessor, new Neuron(), new UnipolarStepFunction());
    std::cout << "Adaline..." << std::endl;
    adaline->initRandomWeights(zeroDeviation);
    adaline->learn(epochs);

    predict(adaline, 0, 0, 0);
    predict(adaline, 0, 1, 0);
    predict(adaline, 1, 0, 0);
    predict(adaline, 1, 1, 1);

    delete adaline;

    delete dataSetAccessor;
    delete dataSet;
    delete enlargedDataSet;
}

void processBipolarAnd(
    const IDataSetReader* dataSetReader,
    const IParametersReader* parametersReader,
    double alpha,
    int epochs,
    double zeroDeviation,
    double bias,
    double minMSE)
{
    std::cout << "\nLearning classifiers for AND with Bipolar step function\n";

    const IDataSet* dataSet = readDataSet(dataSetReader, parametersReader, "../../dataset_and_bipolar.txt");
    const IDataSet* enlargedDataSet = enlargeDataSet(dataSet, parametersReader);
    IDataSetAccessor* dataSetAccessor = prepareDataSetWithAccessor(enlargedDataSet, parametersReader);

    IClassifier* perceptron = new Perceptron(alpha, new double(bias), dataSetAccessor, new Neuron(), new BipolarStepFunction());
    std::cout << "Perceptron...\n";
    perceptron->initRandomWeights(zeroDeviation);
    perceptron->learn(epochs);

    predict(perceptron, -1, -1, -1);
    predict(perceptron, -1, 1, -1);
    predict(perceptron, 1, -1, -1);
    predict(perceptron, 1, 1, 1);

    delete perceptron;

    IClassifier* adaline = new Adaline(alpha, new double(bias), minMSE, dataSetAccessor, new Neuron(), new BipolarStepFunction());
    std::cout << "Adaline...\n";
    adaline->initRandomWeights(zeroDeviation);
    adaline->learn(epochs);

    predict(adaline, -1, -1, -1);
    predict(adaline, -1, 1, -1);
    predict(adaline, 1, -1, -1);
    predict(adaline, 1, 1, 1);

    delete adaline;
}

void processUnipolarOr(
        const IDataSetReader* dataSetReader,
        const IParametersReader* parametersReader,
        double alpha,
        int epochs,
        double zeroDeviation,
        double bias,
        double minMSE)
{
    std::cout << "\nLearning classifiers for OR with Unipolar step function\n";

    const IDataSet* dataSet = readDataSet(dataSetReader, parametersReader, "../../dataset_or_unipolar.txt");
    const IDataSet* enlargedDataSet = enlargeDataSet(dataSet, parametersReader);
    IDataSetAccessor* dataSetAccessor = prepareDataSetWithAccessor(enlargedDataSet, parametersReader);

    IClassifier* perceptron = new Perceptron(alpha, new double(bias), dataSetAccessor, new Neuron(), new UnipolarStepFunction());
    std::cout << "Perceptron..." << std::endl;
    perceptron->initRandomWeights(zeroDeviation);
    perceptron->learn(epochs);

    predict(perceptron, 0, 0, 0);
    predict(perceptron, 0, 1, 1);
    predict(perceptron, 1, 0, 1);
    predict(perceptron, 1, 1, 1);

    delete perceptron;

    IClassifier* adaline = new Adaline(alpha, new double(bias), minMSE, dataSetAccessor, new Neuron(), new UnipolarStepFunction());
    std::cout << "Adaline..." << std::endl;
    adaline->initRandomWeights(zeroDeviation);
    adaline->learn(epochs);

    predict(adaline, 0, 0, 0);
    predict(adaline, 0, 1, 1);
    predict(adaline, 1, 0, 1);
    predict(adaline, 1, 1, 1);

    delete adaline;

    delete dataSetAccessor;
    delete dataSet;
    delete enlargedDataSet;
}

void processBipolarOr(
        const IDataSetReader* dataSetReader,
        const IParametersReader* parametersReader,
        double alpha,
        int epochs,
        double zeroDeviation,
        double bias,
        double minMSE)
{
    std::cout << "\nLearning classifiers for OR with Bipolar step function\n";

    const IDataSet* dataSet = readDataSet(dataSetReader, parametersReader, "../../dataset_or_bipolar.txt");
    const IDataSet* enlargedDataSet = enlargeDataSet(dataSet, parametersReader);
    IDataSetAccessor* dataSetAccessor = prepareDataSetWithAccessor(enlargedDataSet, parametersReader);

    IClassifier* perceptron = new Perceptron(alpha, new double(bias), dataSetAccessor, new Neuron(), new BipolarStepFunction());
    std::cout << "Perceptron...\n";
    perceptron->initRandomWeights(zeroDeviation);
    perceptron->learn(epochs);

    predict(perceptron, -1, -1, -1);
    predict(perceptron, -1, 1, 1);
    predict(perceptron, 1, -1, 1);
    predict(perceptron, 1, 1, 1);

    delete perceptron;

    IClassifier* adaline = new Adaline(alpha, new double(bias), minMSE, dataSetAccessor, new Neuron(), new BipolarStepFunction());
    std::cout << "Adaline...\n";
    adaline->initRandomWeights(zeroDeviation);
    adaline->learn(epochs);

    predict(adaline, -1, -1, -1);
    predict(adaline, -1, 1, 1);
    predict(adaline, 1, -1, 1);
    predict(adaline, 1, 1, 1);

    delete adaline;
}

void predict(IClassifier* classifier, double value1, double value2, int label)
{
    const IData* input = new Data(new double[2] {value1, value2}, new int(label), 2);
    std::cout << "(" << value1 << ", " << value2 << ") = " << classifier->predict(input) << std::endl;
    delete input;
}
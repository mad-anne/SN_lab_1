#include "classifiers/header/Adaline.h"

#include <iostream>

Adaline::Adaline(
        double alpha,
        const double* bias,
        const double minMSE,
        IDataSetAccessor* dataSetAccessor,
        const INeuron* neuron,
        const IActivationFunction* activationFunction) :
        IClassifier(),
        alpha(alpha),
        bias(bias),
        minMSE(minMSE),
        w0(nullptr),
        dataSetAccessor(dataSetAccessor),
        neuron(neuron),
        function(activationFunction),
        weights(nullptr)
{}

Adaline::~Adaline()
{
    delete neuron;
    delete[] weights;
    delete function;
    delete bias;
    delete w0;
}

void Adaline::learn(int epochs)
{
    if (weights == nullptr)
        return;

    for (int i = 0; i < epochs; ++i)
    {
        double mse = learnEpoch();
        if (mse < minMSE)
            break;
    }
}

double Adaline::learnEpoch()
{
    dataSetAccessor->shuffleTrainingSet();
    dataSetAccessor->trainingDataBegin();

    double errorsSum = 0;
    const IData* data;
    while ((data = dataSetAccessor->getNextTrainingData()) != nullptr)
    {
        double output = neuron->processData(data, weights, bias, w0);
        double error = getError(output, *data->getLabel());
        errorsSum += error * error;
        updateWeights(error, data);
    }
    return errorsSum / dataSetAccessor->getDataSet()->getDataSetSize();
}

int Adaline::predict(const IData* data) const
{
    return (int) function->getOutput(neuron->processData(data, weights, bias, w0));
}

double Adaline::getError(double output, double expectedOutput) const
{
    return expectedOutput - output;
}

void Adaline::initRandomWeights(double zeroDeviation)
{
    const size_t dataSize = dataSetAccessor->getDataSet()->getDataSize();

    if (weights == nullptr)
        weights = new double[dataSize];

    for (int i = 0; i < dataSize; ++i)
    {
        double random = ((double) rand() / (double) RAND_MAX);
        weights[i] = 2 * zeroDeviation * random - zeroDeviation;
    }

    if (w0 != nullptr)
        delete w0;

    double random = ((double) rand() / (double) RAND_MAX);
    w0 = new double(2 * zeroDeviation * random - zeroDeviation);
}

void Adaline::updateWeights(double error, const IData* data)
{
    double factor = 2 * alpha * error;
    const size_t dataSize = data->getDataSize();
    const double* inputs = data->getData();

    for (int i = 0; i < dataSize; ++i)
        weights[i] += factor * inputs[i];

    *w0 += factor * (*bias);
}
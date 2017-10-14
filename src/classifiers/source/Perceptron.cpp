#include "classifiers/header/Perceptron.h"

Perceptron::Perceptron(
    double alpha,
    IDataSetAccessor* dataSetAccessor,
    const INeuron* neuron) :
        IClassifier(),
        alpha(alpha),
        dataSetAccessor(dataSetAccessor),
        neuron(neuron),
        weights(nullptr)
{}

Perceptron::~Perceptron()
{
    delete dataSetAccessor;
    delete neuron;
    delete[] weights;
}

void Perceptron::learn(int epochs, double initWeightsDeviation)
{
    initRandomWeights(0.01);
    for (int i = 0; i < epochs; ++i)
        learnEpoch();
}

void Perceptron::learnEpoch()
{
    const IData* data;
    while ((data = dataSetAccessor->getNext()) != nullptr)
    {
        double output = neuron->processData(data, weights);
        double discreteError = getDiscreteError(output, *data->getLabel());
        updateWeights(discreteError, data);
    }
    dataSetAccessor->shuffle();
    dataSetAccessor->begin();
}

int Perceptron::predict(const IData* data) const
{
    return (int) neuron->processData(data, weights);
}

double Perceptron::getDiscreteError(double output, double expectedOutput) const
{
    return expectedOutput - output;
}

void Perceptron::initRandomWeights(double zeroDeviation)
{
    const size_t dataSize = dataSetAccessor->getDataSet()->getDataSize();

    if (weights == nullptr)
        weights = new double[dataSize];

    for (int i = 0; i < dataSize; ++i)
    {
        double random = ((double) rand() / (double) RAND_MAX);
        weights[i] = 2 * zeroDeviation * random - zeroDeviation;
    }
}

void Perceptron::updateWeights(double discreteError, const IData* data)
{
    double factor = alpha * discreteError;
    const size_t dataSize = data->getDataSize();
    const double* inputs = data->getData();

    for (int i = 0; i < dataSize; ++i)
        weights[i] += factor * inputs[i];
}
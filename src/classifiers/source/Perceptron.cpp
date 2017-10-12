#include "classifiers/header/Perceptron.h"

Perceptron::Perceptron(
    double alpha,
    IDataSetAccessor* dataSetAccessor,
    const INeuron* neuron) :
        IClassifier(),
        alpha(alpha),
        dataSetAccessor(dataSetAccessor),
        neuron(neuron)
{}

Perceptron::~Perceptron()
{
    delete dataSetAccessor;
}

void Perceptron::learn(int epochs)
{
    initRandomWeights(0.01);
    for (int i = 0; i < epochs; ++i)
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
}

double Perceptron::getDiscreteError(double output, double expectedOutput) const
{
    return expectedOutput - output;
}

void Perceptron::initRandomWeights(double max)
{
    const size_t dataSize = dataSetAccessor->getDataSet()->getDataSize();
    for (int i = 0; i < dataSize; ++i)
        weights[i] = max * ((double) rand() / (double) RAND_MAX);
}

void Perceptron::updateWeights(double discreteError, const IData* data)
{
    double factor = alpha * discreteError;
    const size_t dataSize = data->getDataSize();
    const double* inputs = data->getData();

    for (int i = 0; i < dataSize; ++i)
        weights[i] += factor * inputs[i];
}

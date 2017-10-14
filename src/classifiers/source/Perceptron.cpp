#include "classifiers/header/Perceptron.h"

Perceptron::Perceptron(
    double alpha,
    const double* bias,
    IDataSetAccessor* dataSetAccessor,
    const INeuron* neuron,
    const IActivationFunction* activationFunction) :
        IClassifier(),
        alpha(alpha),
        bias(bias),
        w0(nullptr),
        dataSetAccessor(dataSetAccessor),
        neuron(neuron),
        function(activationFunction),
        weights(nullptr)
{}

Perceptron::~Perceptron()
{
    delete dataSetAccessor;
    delete neuron;
    delete[] weights;
    delete function;
    delete bias;
    delete w0;
}

void Perceptron::learn(int epochs)
{
    if (weights == nullptr)
        return;

    for (int i = 0; i < epochs; ++i)
        learnEpoch();
}

void Perceptron::learnEpoch()
{
    dataSetAccessor->shuffleTrainingSet();
    dataSetAccessor->trainingDataBegin();

    const IData* data;
    while ((data = dataSetAccessor->getNextTrainingData()) != nullptr)
    {
        double output = function->getOutput(neuron->processData(data, weights, bias, w0));
        double discreteError = getDiscreteError(output, *data->getLabel());
        updateWeights(discreteError, data);
    }
}

int Perceptron::predict(const IData* data) const
{
    return (int) function->getOutput(neuron->processData(data, weights, bias, w0));
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

    if (w0 != nullptr)
        delete w0;

    double random = ((double) rand() / (double) RAND_MAX);
    w0 = new double(2 * zeroDeviation * random - zeroDeviation);
}

void Perceptron::updateWeights(double discreteError, const IData* data)
{
    double factor = alpha * discreteError;
    const size_t dataSize = data->getDataSize();
    const double* inputs = data->getData();

    for (int i = 0; i < dataSize; ++i)
        weights[i] += factor * inputs[i];

    *w0 += factor * (*bias);
}
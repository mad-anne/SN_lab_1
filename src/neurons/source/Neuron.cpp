#include "neurons/header/Neuron.h"

Neuron::Neuron(const IActivationFunction* function) :
    INeuron(),
    function(function)
{

}

Neuron::~Neuron()
{
    delete function;
}

double Neuron::processData(const IData* data, double* weights) const
{
    double output = getNet(data->getData(), weights, data->getDataSize());
    return function->getOutput(output);
}

double Neuron::getNet(const double* inputs, const double* weights, const size_t dataSize) const
{
    double sum = 0;
    for (int i = 0; i < dataSize; ++i)
        sum += inputs[i] * weights[i];
    return sum;
}
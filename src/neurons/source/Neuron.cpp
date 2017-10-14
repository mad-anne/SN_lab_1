#include "neurons/header/Neuron.h"

Neuron::Neuron() :
    INeuron()
{}

Neuron::~Neuron()
{}

double Neuron::processData(const IData* data, double* weights) const
{
    return getNet(data->getData(), weights, data->getDataSize());
}

double Neuron::getNet(const double* inputs, const double* weights, const size_t dataSize) const
{
    double sum = 0;
    for (int i = 0; i < dataSize; ++i)
        sum += inputs[i] * weights[i];
    return sum;
}
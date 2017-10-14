#include "neurons/header/Neuron.h"

Neuron::Neuron()
= default;

Neuron::~Neuron()
= default;

double Neuron::processData(const IData* data, double* weights, const double* bias, const double* w0) const
{
    return getNet(data->getData(), weights, data->getDataSize(), bias, w0);
}

double Neuron::getNet(const double* inputs, const double* weights, const size_t dataSize, const double* bias, const double* w0) const
{
    double sum = 0;
    for (int i = 0; i < dataSize; ++i)
        sum += inputs[i] * weights[i];
    return sum + (*bias) * (*w0);
}
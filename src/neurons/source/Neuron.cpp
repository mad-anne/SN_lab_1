#include "neurons/header/Neuron.h"

Neuron::Neuron(int numberOfInputs, double alfa) :
    INeuron(),
    numberOfInputs(numberOfInputs),
    alfa(alfa)
{}

Neuron::~Neuron()
{}

double Neuron::getDiscreteError(double output, double expectedOutput) const
{
    return expectedOutput - output;
}

double Neuron::getNet(double* inputs, double* weights) const
{
    double sum = 0;
    for (int i = 0; i < numberOfInputs; ++i)
        sum += inputs[i] * weights[i];
    return sum;
}
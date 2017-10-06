#include "neurons/header/Neuron.h"

Neuron::Neuron()
{}

Neuron::~Neuron()
{}

double Neuron::getDiscreteError(double output, double expectedOutput) const
{
    return expectedOutput - output;
}
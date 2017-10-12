#include "classifiers/header/Perceptron.h"

Perceptron::Perceptron(
    IDataSetAccessor* dataSetAccessor, const INeuron* neuron) :
        IClassifier(),
        dataSetAccessor(dataSetAccessor),
        neuron(neuron)
{}

Perceptron::~Perceptron()
{
    delete dataSetAccessor;
}

void Perceptron::learn(int epochs) const
{
    for (int i = 0; i < epochs; ++i)
    {
        const IData* data;
        while ((data = dataSetAccessor->getNext()) != nullptr)
        {

        }
    }
}

double Perceptron::getDiscreteError(double output, double expectedOutput) const
{
    return expectedOutput - output;
}
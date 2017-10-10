#include "classifiers/header/Perceptron.h"

Perceptron::Perceptron(
    const IDataSetAccessor* dataSetAccessor) :
        IClassifier(),
        dataSetAccessor(dataSetAccessor)
{}

Perceptron::~Perceptron()
{
    delete dataSetAccessor;
}

void Perceptron::learn() const
{

}
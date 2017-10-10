#include "datasets/header/DataSet.h"

DataSet::DataSet(
    double** inputs,
    int* labels,
    int numberOfInputs,
    int inputSize) :
        inputs(inputs),
        labels(labels),
        numberOfInputs(numberOfInputs),
        inputSize(inputSize)
{}

DataSet::~DataSet()
{
    for (int i = 0; i < numberOfInputs; ++i)
        delete[] inputs[i];
    delete[] inputs;
    delete[] labels;
}

double* DataSet::getData(int index) const
{
    if (0 <= index < numberOfInputs)
        return inputs[index];
    return nullptr;
}

int DataSet::getDataSetSize() const
{
    return numberOfInputs;
}

int DataSet::getDataSize() const
{
    return inputSize;
}
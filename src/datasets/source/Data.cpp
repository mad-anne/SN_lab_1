#include "datasets/header/Data.h"

Data::Data(
    const double* data,
    const int* label,
    const size_t dataSize) :
        IData(),
        data(data),
        label(label),
        dataSize(dataSize)
{}

Data::~Data()
{
    delete[] data;
    delete label;
}

const double* Data::getData() const
{
    return data;
}

const int* Data::getLabel() const
{
    return label;
}

const size_t Data::getDataSize() const
{
    return dataSize;
}
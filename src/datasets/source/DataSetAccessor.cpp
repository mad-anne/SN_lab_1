#include <algorithm>
#include <numeric>
#include <vector>
#include <random>

#include "datasets/header/DataSetAccessor.h"

DataSetAccessor::DataSetAccessor(const IDataSet* dataSet) :
    IDataSetAccessor(dataSet),
    dataIndexes(dataSet->getDataSetSize()),
    currDataIndex(0)
{
    std::iota(dataIndexes.begin(), dataIndexes.end(), dataSet->getDataSetSize());
}

DataSetAccessor::~DataSetAccessor()
{}

void DataSetAccessor::shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(dataIndexes.begin(), dataIndexes.end(), g);
}

double* DataSetAccessor::getNext()
{
    double* nextData = dataSet->getData(currDataIndex);
    if (nextData != nullptr)
        ++currDataIndex;
    return nextData;
}

void DataSetAccessor::begin()
{
    currDataIndex = 0;
}

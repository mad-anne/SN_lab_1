#include <algorithm>
#include <numeric>
#include <vector>
#include <random>
#include <iostream>

#include "datasets/header/DataSetAccessor.h"

DataSetAccessor::DataSetAccessor(
    const IDataSet* dataSet) :
        IDataSetAccessor(),
        dataSet(dataSet),
        indexes(dataSet->getDataSetSize()),
        it(indexes.begin())
{
    std::iota(indexes.begin(), indexes.end(), 0);
}

DataSetAccessor::~DataSetAccessor()
= default;

void DataSetAccessor::shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indexes.begin(), indexes.end(), g);
}

const IData* DataSetAccessor::getNext()
{
    return it != indexes.end() ? dataSet->getData(*it++) : nullptr;
}

void DataSetAccessor::begin()
{
    it = indexes.begin();
}

const IDataSet* DataSetAccessor::getDataSet() const
{
    return dataSet;
}
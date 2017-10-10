#include <vector>
#include <iostream>
#include "datasets/header/DataSet.h"

DataSet::DataSet(
    std::vector<const IData*>* dataSet,
    const size_t dataSize,
    const size_t dataSetSize) :
        IDataSet(),
        dataSet(dataSet),
        dataSize(dataSize),
        dataSetSize(dataSetSize)
{}

DataSet::~DataSet()
{
    clearDataSet();
}

void DataSet::clearDataSet()
{
    for (auto &it : (*dataSet))
        delete it;
    (*dataSet).clear();
    delete dataSet;
}

const IData* DataSet::getData(const int index) const
{
    if (0 <= index && index < dataSetSize)
    {
        int size = (*dataSet).size();
        const IData* data = (*dataSet).at(index);
        return data;
    }
    return nullptr;
}

const size_t DataSet::getDataSetSize() const
{
    return dataSetSize;
}

const size_t DataSet::getDataSize() const
{
    return dataSize;
}
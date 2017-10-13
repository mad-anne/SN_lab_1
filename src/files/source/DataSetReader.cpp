#include <fstream>
#include <iostream>

#include "datasets/header/Data.h"
#include "files/header/DataSetReader.h"

DataSetReader::DataSetReader()
{}

DataSetReader::~DataSetReader()
{}

const IDataSet* DataSetReader::readDataSet(std::string fileName, size_t dataSize) const
{
    auto* _dataSet = new std::vector<const IData*>();
    int label;
    std::string line;
    double input;
    std::ifstream infile(fileName);
    while (infile >> label)
    {
        auto* data = new double[dataSize];
        for (int i = 0; i < dataSize; ++i)
        {
            infile >> input;
            data[i] = input;
        }

        _dataSet->push_back(new Data(data, new int(label), dataSize));
    }
    infile.close();
    return new DataSet(_dataSet, dataSize, _dataSet->size());
}
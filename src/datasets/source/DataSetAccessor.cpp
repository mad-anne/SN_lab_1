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
        indexes(dataSet->getDataSetSize())
{
    std::iota(indexes.begin(), indexes.end(), 0);
}

DataSetAccessor::~DataSetAccessor()
= default;

void DataSetAccessor::splitDataSet(double trainingPart, double validatingPart, double testingPart)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indexes.begin(), indexes.end(), g);

    double breakPoint_1 = indexes.size() * trainingPart;
    double breakPoint_2 = breakPoint_1 + indexes.size() * validatingPart;

    trainingSetIndexes = std::vector<int>(indexes.begin(), indexes.begin() + breakPoint_1);
    validatingSetIndexes = std::vector<int>(indexes.begin() + breakPoint_1, indexes.begin() + breakPoint_2);
    testingSetIndexes = std::vector<int>(indexes.begin() + breakPoint_2, indexes.end());
}

void DataSetAccessor::trainingDataBegin()
{
    trainingIt = trainingSetIndexes.begin();
}

void DataSetAccessor::validatingDataBegin()
{
    validatingIt = validatingSetIndexes.begin();
}

void DataSetAccessor::testingDataBegin()
{
    testingIt = testingSetIndexes.begin();
}

const IData* DataSetAccessor::getNextTrainingData()
{
    return trainingIt != trainingSetIndexes.end() ? dataSet->getData(*trainingIt++) : nullptr;
}

const IData* DataSetAccessor::getNextValidatingData()
{
    return validatingIt != validatingSetIndexes.end() ? dataSet->getData(*validatingIt++) : nullptr;
}

const IData* DataSetAccessor::getNextTestingData()
{
    return testingIt != testingSetIndexes.end() ? dataSet->getData(*testingIt++) : nullptr;
}

void DataSetAccessor::shuffleTrainingSet()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(trainingSetIndexes.begin(), trainingSetIndexes.end(), g);
}

const IDataSet* DataSetAccessor::getDataSet() const
{
    return dataSet;
}


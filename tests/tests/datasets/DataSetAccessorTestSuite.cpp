#include <gtest/gtest.h>

#include "datasets/header/Data.h"
#include "datasets/header/DataSet.h"
#include "datasets/header/DataSetAccessor.h"

const size_t DATA_SET_SIZE = 4;
const size_t DATA_SIZE = 2;

class DataSetAccessorTestSuite : public ::testing::Test
{
    public:
        DataSetAccessorTestSuite();
        ~DataSetAccessorTestSuite();

    protected:
        std::vector<const IData*>* _dataSet;
        IDataSet* dataSet;
        IDataSetAccessor* sut;

        void initDataSet();
};

DataSetAccessorTestSuite::DataSetAccessorTestSuite() :
    _dataSet(new std::vector<const IData*>()),
    dataSet(new DataSet(_dataSet, DATA_SIZE, DATA_SET_SIZE)),
    sut(new DataSetAccessor(dataSet))
{
    initDataSet();
    sut->splitDataSet(0.75, 0, 0.25);
    sut->trainingDataBegin();
}

DataSetAccessorTestSuite::~DataSetAccessorTestSuite()
{
    delete dataSet;
    delete sut;
}

void DataSetAccessorTestSuite::initDataSet()
{
    (*_dataSet).push_back(new Data(new double[DATA_SIZE] {0, 0}, new int(0), DATA_SIZE));
    (*_dataSet).push_back(new Data(new double[DATA_SIZE] {0, 1}, new int(0), DATA_SIZE));
    (*_dataSet).push_back(new Data(new double[DATA_SIZE] {1, 0}, new int(0), DATA_SIZE));
    (*_dataSet).push_back(new Data(new double[DATA_SIZE] {1, 1}, new int(1), DATA_SIZE));
}

TEST_F(DataSetAccessorTestSuite, getNextReturnsNullptrAfterLastData)
{
    sut->getNextTrainingData();
    sut->getNextTrainingData();
    sut->getNextTrainingData();
    ASSERT_EQ(sut->getNextTrainingData(), nullptr);
}

TEST_F(DataSetAccessorTestSuite, beginSetsAccessorToFirstElement)
{
    const IData* data = sut->getNextTrainingData();
    sut->trainingDataBegin();
    ASSERT_EQ(sut->getNextTrainingData(), data);
}

TEST_F(DataSetAccessorTestSuite, afterShuffleAccessorContainsAllElements)
{
    sut->getNextTrainingData();
    sut->trainingDataBegin();
    ASSERT_NE(sut->getNextTrainingData(), nullptr);
    ASSERT_NE(sut->getNextTrainingData(), nullptr);
    ASSERT_NE(sut->getNextTrainingData(), nullptr);
    ASSERT_EQ(sut->getNextTrainingData(), nullptr);
}
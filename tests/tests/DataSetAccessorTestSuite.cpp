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

        bool dataSetContainsData(const IData* data);
        void initDataSet();
};

DataSetAccessorTestSuite::DataSetAccessorTestSuite() :
    _dataSet(new std::vector<const IData*>()),
    dataSet(new DataSet(_dataSet, DATA_SIZE, DATA_SET_SIZE)),
    sut(new DataSetAccessor(dataSet))
{
    initDataSet();
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

bool DataSetAccessorTestSuite::dataSetContainsData(const IData* data)
{
    for (int i = 0; i < DATA_SET_SIZE; ++i)
        if (dataSet->getData(i) == data)
            return true;
    return false;
}

TEST_F(DataSetAccessorTestSuite, getNextReturnsFirstDataOnInit)
{
    ASSERT_EQ(sut->getNext(), (*_dataSet).at(0));
}

TEST_F(DataSetAccessorTestSuite, getNextReturnsNextData)
{
    sut->getNext();
    sut->getNext();
    ASSERT_EQ(sut->getNext(), (*_dataSet).at(2));
}

TEST_F(DataSetAccessorTestSuite, getNextReturnsNullptrAfterLastData)
{
    sut->getNext();
    sut->getNext();
    sut->getNext();
    sut->getNext();
    ASSERT_EQ(sut->getNext(), nullptr);
}

TEST_F(DataSetAccessorTestSuite, beginSetsAccessorToFirstElement)
{
    sut->getNext();
    sut->begin();
    ASSERT_EQ(sut->getNext(), (*_dataSet).at(0));
}

TEST_F(DataSetAccessorTestSuite, afterShuffleAccessorContainsAllElements)
{
    sut->shuffle();
    sut->begin();
    ASSERT_TRUE(dataSetContainsData(sut->getNext()));
    ASSERT_TRUE(dataSetContainsData(sut->getNext()));
    ASSERT_TRUE(dataSetContainsData(sut->getNext()));
    ASSERT_TRUE(dataSetContainsData(sut->getNext()));
    ASSERT_FALSE(dataSetContainsData(sut->getNext()));
}
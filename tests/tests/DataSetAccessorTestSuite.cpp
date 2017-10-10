#include <gtest/gtest.h>

#include "datasets/header/DataSet.h"
#include "datasets/header/DataSetAccessor.h"

const short DATASET_SIZE = 4;
const short DATA_SIZE = 2;

int initialData[DATASET_SIZE][DATA_SIZE] = {
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1}
};

int initialLabels[DATASET_SIZE] = {0, 0, 0, 1};

class DataSetAccessorTestSuite : public ::testing::Test
{
    public:
        DataSetAccessorTestSuite();
        ~DataSetAccessorTestSuite();

    protected:
        int dataSetSize;
        int dataSize;
        double** data;
        int* labels;
        IDataSet* dataSet;
        IDataSetAccessor* sut;

        bool dataSetContainsData(double* data);

    private:
        double** getInitialData();
        int* getInitialLabels();

        void clearData();
};

DataSetAccessorTestSuite::DataSetAccessorTestSuite() :
    dataSetSize(DATASET_SIZE),
    dataSize(DATA_SIZE),
    data(getInitialData()),
    labels(getInitialLabels()),
    dataSet(new DataSet(data, labels, dataSetSize, dataSize)),
    sut(new DataSetAccessor(dataSet))
{}

DataSetAccessorTestSuite::~DataSetAccessorTestSuite()
{
    clearData();
    delete[] labels;
    delete dataSet;
    delete sut;
}

double** DataSetAccessorTestSuite::getInitialData()
{
    double** tempData = new double*[dataSetSize];

    for (int i = 0; i < dataSetSize; ++i)
    {
        tempData[i] = new double[dataSize];

        for (int j = 0; j < dataSize; ++j)
            tempData[i][j] = initialData[i][j];
    }

    return tempData;
}

int* DataSetAccessorTestSuite::getInitialLabels()
{
    int* tempLabels = new int[dataSetSize];

    for (int i = 0; i < dataSize; ++i)
        tempLabels[i] = initialLabels[i];

    return tempLabels;
}

void DataSetAccessorTestSuite::clearData()
{
    for (int i = dataSetSize - 1; i >= 0; --i)
        delete[] data[i];

    delete[] data;
}

bool DataSetAccessorTestSuite::dataSetContainsData(double* data)
{
    for (int i = 0; i < DATASET_SIZE; ++i)
        if (dataSet->getData(i) == data)
            return true;
    return false;
}

TEST_F(DataSetAccessorTestSuite, getNextReturnsFirstDataOnInit)
{
    ASSERT_EQ(sut->getNext(), data[0]);
}

TEST_F(DataSetAccessorTestSuite, getNextReturnsNextData)
{
    sut->getNext();
    sut->getNext();
    ASSERT_EQ(sut->getNext(), data[2]);
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
    ASSERT_EQ(sut->getNext(), data[0]);
}

TEST_F(DataSetAccessorTestSuite, afterShuffleAccessorContainsAllElements)
{
    sut->shuffle();
    ASSERT_TRUE(dataSetContainsData(sut->getNext()));
    ASSERT_TRUE(dataSetContainsData(sut->getNext()));
    ASSERT_TRUE(dataSetContainsData(sut->getNext()));
    ASSERT_TRUE(dataSetContainsData(sut->getNext()));
    ASSERT_FALSE(dataSetContainsData(sut->getNext()));
}
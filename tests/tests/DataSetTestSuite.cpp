#include <gtest/gtest.h>

#include "datasets/header/Data.h"
#include "datasets/header/DataSet.h"

const size_t DATA_SET_SIZE = 4;
const size_t DATA_SIZE = 2;

class DataSetTestSuite : public ::testing::Test
{
    public:
        DataSetTestSuite();
        ~DataSetTestSuite();

    protected:
        std::vector<const IData*>* dataSet;
        IDataSet* sut;

        void initDataSet();
};

DataSetTestSuite::DataSetTestSuite() :
    dataSet(new std::vector<const IData*>()),
    sut(new DataSet(dataSet, DATA_SIZE, DATA_SET_SIZE))
{
    initDataSet();
}

DataSetTestSuite::~DataSetTestSuite()
{
    delete sut;
}

void DataSetTestSuite::initDataSet()
{
    (*dataSet).push_back(new Data(new double[DATA_SIZE] {0, 0}, new int(0), DATA_SIZE));
    (*dataSet).push_back(new Data(new double[DATA_SIZE] {0, 1}, new int(0), DATA_SIZE));
    (*dataSet).push_back(new Data(new double[DATA_SIZE] {1, 0}, new int(0), DATA_SIZE));
    (*dataSet).push_back(new Data(new double[DATA_SIZE] {1, 1}, new int(1), DATA_SIZE));
}

TEST_F(DataSetTestSuite, getDataOfIndexReturnsPtrToCorrectData)
{
    ASSERT_EQ(sut->getData(1), (*dataSet).at(1));
}

TEST_F(DataSetTestSuite, getDataOfIndexReturnsNullptrWhenIndexExceeds)
{
    ASSERT_EQ(sut->getData(5), nullptr);
}


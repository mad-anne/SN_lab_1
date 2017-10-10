#include <gtest/gtest.h>

#include "datasets/header/Data.h"

const size_t DATA_SIZE = 2;

class DataTestSuite : public ::testing::Test
{
    public:
        DataTestSuite();
        ~DataTestSuite();

    protected:
        double* data;
        int* label;
        IData* sut;
};

DataTestSuite::DataTestSuite() :
    data(new double[DATA_SIZE]),
    label(new int(1)),
    sut(new Data(data, label, DATA_SIZE))
{}

DataTestSuite::~DataTestSuite()
{
    delete sut;
}

TEST_F(DataTestSuite, getDataReturnsDataPassedToConstructor)
{
    ASSERT_EQ(sut->getData(), data);
}

TEST_F(DataTestSuite, getLabelReturnsLabelPassedToConstructor)
{
    ASSERT_EQ(sut->getLabel(), label);
}

TEST_F(DataTestSuite, getDataSizeReturnsSameSizeAsPassedToConstructor)
{
    ASSERT_EQ(sut->getDataSize(), DATA_SIZE);
}
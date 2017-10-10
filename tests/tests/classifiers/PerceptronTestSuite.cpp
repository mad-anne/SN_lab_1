#include <gtest/gtest.h>

#include "classifiers/header/Perceptron.h"
#include "datasets/header/Data.h"
#include "datasets/header/DataSet.h"
#include "datasets/header/DataSetAccessor.h"

const size_t DATA_SET_SIZE = 4;
const size_t DATA_SIZE = 2;

class PerceptronTestSuite : public ::testing::Test
{
    public:
        PerceptronTestSuite();
        ~PerceptronTestSuite();

    protected:
        std::vector<const IData*>* _dataSet;
        IDataSet* dataSet;
        IDataSetAccessor* dataSetAccessor;
        Perceptron* sut;

        void initDataSet();
};

PerceptronTestSuite::PerceptronTestSuite() :
    _dataSet(new std::vector<const IData*>()),
    dataSet(new DataSet(_dataSet, DATA_SIZE, DATA_SET_SIZE)),
    dataSetAccessor(new DataSetAccessor(dataSet)),
    sut(new Perceptron(dataSetAccessor))
{
    initDataSet();
}

PerceptronTestSuite::~PerceptronTestSuite()
{
    delete dataSet;
    delete sut;
}

void PerceptronTestSuite::initDataSet()
{
    (*_dataSet).push_back(new Data(new double[DATA_SIZE] {0, 0}, new int(0), DATA_SIZE));
    (*_dataSet).push_back(new Data(new double[DATA_SIZE] {0, 1}, new int(0), DATA_SIZE));
    (*_dataSet).push_back(new Data(new double[DATA_SIZE] {1, 0}, new int(0), DATA_SIZE));
    (*_dataSet).push_back(new Data(new double[DATA_SIZE] {1, 1}, new int(1), DATA_SIZE));
}

TEST_F(PerceptronTestSuite, canCreateObject)
{
    ASSERT_TRUE(true);
}
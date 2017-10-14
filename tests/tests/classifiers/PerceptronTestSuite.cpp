#include <gtest/gtest.h>

#include "classifiers/header/Perceptron.h"
#include "datasets/header/Data.h"
#include "datasets/header/DataSet.h"
#include "datasets/header/DataSetAccessor.h"
#include "functions/header/UnipolarStepFunction.h"
#include "neurons/header/Neuron.h"

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
        double theta;
        const IActivationFunction* function;
        INeuron* neuron;
        double alpha;
        Perceptron* sut;

        void initDataSet();
};

PerceptronTestSuite::PerceptronTestSuite() :
    _dataSet(new std::vector<const IData*>()),
    dataSet(new DataSet(_dataSet, DATA_SIZE, DATA_SET_SIZE)),
    dataSetAccessor(new DataSetAccessor(dataSet)),
    theta(0.5),
    function(new UnipolarStepFunction(theta)),
    neuron(new Neuron()),
    alpha(0.01),
    sut(new Perceptron(alpha, dataSetAccessor, neuron, function))
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
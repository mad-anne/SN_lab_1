#include <gtest/gtest.h>

#include "datasets/header/Data.h"
#include "functions/header/UnipolarStepFunction.h"
#include "neurons/header/Neuron.h"

const size_t DATA_SIZE = 3;

class NeuronTestSuite : public ::testing::Test
{
    public:
        NeuronTestSuite();
        ~NeuronTestSuite();

    protected:
        const IData* data;
        double theta;
        const IActivationFunction* function;
        INeuron* sut;
};

NeuronTestSuite::NeuronTestSuite() :
    data(new Data(new double[DATA_SIZE] {1, 0, 1}, new int(0), DATA_SIZE)),
    theta(0.5),
    function(new UnipolarStepFunction(theta)),
    sut(new Neuron(function))
{}

NeuronTestSuite::~NeuronTestSuite()
{
    delete data;
    delete sut;
}

TEST_F(NeuronTestSuite, processDataWhenOutputDifferenceGreaterThanTheta)
{
    auto * weights = new double[3] { 0.28, 0.33, 0.32 };

    ASSERT_EQ(sut->processData(data, weights), 1);

    delete weights;
}

TEST_F(NeuronTestSuite, processDataWhenOutputDifferenceLessThanTheta)
{
    auto * weights = new double[3] { 0.14, 0.33, 0.32 };

    ASSERT_EQ(sut->processData(data, weights), 0);

    delete weights;
}
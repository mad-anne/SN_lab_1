#include <gtest/gtest.h>

#include "neurons/interface/INeuron.h"
#include "neurons/header/Neuron.h"

class NeuronTestSuite : public ::testing::Test
{
    public:
        NeuronTestSuite();
        ~NeuronTestSuite();

    protected:
        double theta;
        INeuron* sut;
        double alfa;
        int numberOfInputs;
};

NeuronTestSuite::NeuronTestSuite() :
    numberOfInputs(4),
    alfa(0.5),
    sut(new Neuron(numberOfInputs, alfa))
{}

NeuronTestSuite::~NeuronTestSuite()
{
    delete sut;
}

TEST_F(NeuronTestSuite, getDiscreteErrorReturnsOutputsDifference)
{
    double output = 0;
    double expectedOutput = 1;
    ASSERT_EQ(sut->getDiscreteError(output, expectedOutput), 1);
}

TEST_F(NeuronTestSuite, getNetReturnsWeightedSumOfInputs)
{
    double* inputs = new double[2] { 0.5, 1.0 };
    double* weights = new double[2] { 0.28, 0.33 };
    double result = 0.5 * 0.28 + 0.33;

    ASSERT_EQ(sut->getNet(inputs, weights), result);

    delete[] inputs;
    delete[] weights;
}
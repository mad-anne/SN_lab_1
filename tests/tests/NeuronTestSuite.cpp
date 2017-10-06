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
};

NeuronTestSuite::NeuronTestSuite() :
    sut(new Neuron())
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
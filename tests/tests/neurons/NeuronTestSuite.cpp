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
        INeuron* sut;
};

NeuronTestSuite::NeuronTestSuite() :
    data(new Data(new double[DATA_SIZE] {1, 0, 1}, new int(0), DATA_SIZE)),
    sut(new Neuron())
{}

NeuronTestSuite::~NeuronTestSuite()
{
    delete data;
    delete sut;
}

TEST_F(NeuronTestSuite, processDataReturnsCorrectOutput)
{
    auto * weights = new double[3] { 0.14, 0.33, 0.32 };

    ASSERT_EQ(sut->processData(data, weights), 0.46);

    delete weights;
}
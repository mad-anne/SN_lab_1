#include <gtest/gtest.h>

#include "functions/interface/IActivationFunction.h"
#include "functions/header/BipolarStepFunction.h"

class BipolarStepFunctionTestSuite : public ::testing::Test
{
    public:
        BipolarStepFunctionTestSuite();
        ~BipolarStepFunctionTestSuite();

    protected:
        IActivationFunction* sut;
};

BipolarStepFunctionTestSuite::BipolarStepFunctionTestSuite() :
        sut(new BipolarStepFunction())
{}

BipolarStepFunctionTestSuite::~BipolarStepFunctionTestSuite()
{
    delete sut;
}

TEST_F(BipolarStepFunctionTestSuite, returnsMinusOneWhenValueIsLessThanZero)
{
    ASSERT_EQ(sut->getOutput(-0.01), -1);
}

TEST_F(BipolarStepFunctionTestSuite, returnsOneWhenValueIsEqualToZero)
{
    ASSERT_EQ(sut->getOutput(0), 1);
}

TEST_F(BipolarStepFunctionTestSuite, returnsOneWhenValueIsGreaterThanZero)
{
    ASSERT_EQ(sut->getOutput(0.01), 1);
}

#include <gtest/gtest.h>

#include "functions/interface/IActivationFunction.h"
#include "functions/header/UnipolarStepFunction.h"

class UnipolarStepFunctionTestSuite : public ::testing::Test
{
    public:
        UnipolarStepFunctionTestSuite();
        ~UnipolarStepFunctionTestSuite();

    protected:
        IActivationFunction* sut;
};

UnipolarStepFunctionTestSuite::UnipolarStepFunctionTestSuite() :
    sut(new UnipolarStepFunction())
{}

UnipolarStepFunctionTestSuite::~UnipolarStepFunctionTestSuite()
{
    delete sut;
}

TEST_F(UnipolarStepFunctionTestSuite, returnsZeroWhenValueIsLessThanZero)
{
    ASSERT_EQ(sut->getOutput(-0.01), 0);
}

TEST_F(UnipolarStepFunctionTestSuite, returnsOneWhenValueIsEqualToZero)
{
    ASSERT_EQ(sut->getOutput(0), 1);
}

TEST_F(UnipolarStepFunctionTestSuite, returnsOneWhenValueIsGreaterThanZero)
{
    ASSERT_EQ(sut->getOutput(0.01), 1);
}
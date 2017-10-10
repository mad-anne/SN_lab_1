#include <gtest/gtest.h>

#include "functions/interface/IActivationFunction.h"
#include "functions/header/UnipolarStepFunction.h"

class UnipolarStepFunctionTestSuite : public ::testing::Test
{
    public:
        UnipolarStepFunctionTestSuite();
        ~UnipolarStepFunctionTestSuite();

    protected:
        double theta;
        IActivationFunction* sut;
};

UnipolarStepFunctionTestSuite::UnipolarStepFunctionTestSuite() :
    theta(0.5),
    sut(new UnipolarStepFunction(theta))
{}

UnipolarStepFunctionTestSuite::~UnipolarStepFunctionTestSuite()
{
    delete sut;
}

TEST_F(UnipolarStepFunctionTestSuite, returnsZeroWhenValueIsLessThanTheta)
{
    double value = theta - 0.01;
    ASSERT_EQ(sut->getOutput(value), 0);
}

TEST_F(UnipolarStepFunctionTestSuite, returnsOneWhenValueIsEqualToTheta)
{
    ASSERT_EQ(sut->getOutput(theta), 1);
}

TEST_F(UnipolarStepFunctionTestSuite, returnsOneWhenValueIsGreaterThanTheta)
{
    double value = theta + 0.01;
    ASSERT_EQ(sut->getOutput(value), 1);
}
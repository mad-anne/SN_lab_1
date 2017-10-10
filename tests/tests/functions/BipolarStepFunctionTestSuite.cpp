#include <gtest/gtest.h>

#include "functions/interface/IActivationFunction.h"
#include "functions/header/BipolarStepFunction.h"

class BipolarStepFunctionTestSuite : public ::testing::Test
{
    public:
        BipolarStepFunctionTestSuite();
        ~BipolarStepFunctionTestSuite();

    protected:
        double theta;
        IActivationFunction* sut;
};

BipolarStepFunctionTestSuite::BipolarStepFunctionTestSuite() :
        theta(0.5),
        sut(new BipolarStepFunction(theta))
{}

BipolarStepFunctionTestSuite::~BipolarStepFunctionTestSuite()
{
    delete sut;
}

TEST_F(BipolarStepFunctionTestSuite, returnsMinusOneWhenValueIsLessThanTheta)
{
    double value = theta - 0.01;
    ASSERT_EQ(sut->getOutput(value), -1);
}

TEST_F(BipolarStepFunctionTestSuite, returnsOneWhenValueIsEqualToTheta)
{
    ASSERT_EQ(sut->getOutput(theta), 1);
}

TEST_F(BipolarStepFunctionTestSuite, returnsOneWhenValueIsGreaterThanTheta)
{
    double value = theta + 0.01;
    ASSERT_EQ(sut->getOutput(value), 1);
}

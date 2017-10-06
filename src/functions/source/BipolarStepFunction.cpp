#include "functions/header/BipolarStepFunction.h"

BipolarStepFunction::BipolarStepFunction(double theta) :
        IActivationFunction(),
        theta(theta)
{}

BipolarStepFunction::~BipolarStepFunction()
{}

double BipolarStepFunction::getOutput(double input) const
{
    if (input < theta)
        return -1.0;
    return 1.0;
}
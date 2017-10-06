#include "functions/header/UnipolarStepFunction.h"

UnipolarStepFunction::UnipolarStepFunction(double theta) :
    IActivationFunction(),
    theta(theta)
{}

UnipolarStepFunction::~UnipolarStepFunction()
{}

double UnipolarStepFunction::getOutput(double input) const
{
    if (input < theta)
        return 0.0;
    return 1.0;
}
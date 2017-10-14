#include "functions/header/UnipolarStepFunction.h"

UnipolarStepFunction::UnipolarStepFunction()
= default;

UnipolarStepFunction::~UnipolarStepFunction()
= default;

double UnipolarStepFunction::getOutput(double input) const
{
    if (input < 0)
        return 0.0;
    return 1.0;
}
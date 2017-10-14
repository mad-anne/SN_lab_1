#include "functions/header/BipolarStepFunction.h"

BipolarStepFunction::BipolarStepFunction()
= default;

BipolarStepFunction::~BipolarStepFunction()
= default;

double BipolarStepFunction::getOutput(double input) const
{
    if (input < 0)
        return -1.0;
    return 1.0;
}
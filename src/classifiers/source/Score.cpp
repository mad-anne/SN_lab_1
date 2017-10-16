#include <cstdlib>
#include "classifiers/header/Score.h"


Score::Score()
= default;

Score::~Score()
= default;

void Score::addTruePositives(int value)
{
    truePositives += value;
}

void Score::addTrueNegatives(int value)
{
    trueNegatives += value;
}

void Score::addFalsePositives(int value)
{
    falsePositives += value;
}

void Score::addFalseNegatives(int value)
{
    falseNegatives += value;
}

void Score::reset()
{
    truePositives = 0;
    trueNegatives = 0;
    falsePositives = 0;
    falseNegatives = 0;
}

double Score::getAccuracy() const
{
    return ((truePositives + trueNegatives) / (truePositives + trueNegatives + falsePositives + falseNegatives)) * 100;
}
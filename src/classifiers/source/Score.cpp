#include <cstdlib>
#include "classifiers/header/Score.h"


Score::Score(const size_t dataSetSize) :
    dataSetSize(dataSetSize)
{}

Score::~Score()
= default;

void Score::setTruePositives(int value)
{
    truePositives = value;
}

void Score::setTrueNegatives(int value)
{
    trueNegatives = value;
}

void Score::setFalsePositives(int value)
{
    falsePositives = value;
}

void Score::setFalseNegatives(int value)
{
    falseNegatives = value;
}
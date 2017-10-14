#ifndef SN_LAB_1_ICLASSIFIER_H
#define SN_LAB_1_ICLASSIFIER_H

#include "datasets/interface/IData.h"

class IClassifier
{
    public:
        virtual ~IClassifier() = default;

        virtual void learn(int epochs, double initWeightsDeviation) = 0;
        virtual int predict(const IData* data) const = 0;
};

#endif //SN_LAB_1_ICLASSIFIER_H

#ifndef SN_LAB_1_ICLASSIFIER_H
#define SN_LAB_1_ICLASSIFIER_H

#include "datasets/interface/IData.h"

class IClassifier
{
    public:
        ~IClassifier() = default;

        virtual void learn(int epochs) = 0;
        virtual int predict(const IData* data) const = 0;
};

#endif //SN_LAB_1_ICLASSIFIER_H

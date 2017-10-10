#ifndef SN_LAB_1_PERCEPTRON_H
#define SN_LAB_1_PERCEPTRON_H

#include "classifiers/interface/IClassifier.h"
#include "datasets/interface/IDataSetAccessor.h"

class Perceptron : public IClassifier
{
    const IDataSetAccessor* dataSetAccessor;

    public:
        Perceptron(const IDataSetAccessor* dataSetAccessor);
        ~Perceptron();

        void learn() const override;
};


#endif //SN_LAB_1_PERCEPTRON_H

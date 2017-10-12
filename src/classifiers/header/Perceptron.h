#ifndef SN_LAB_1_PERCEPTRON_H
#define SN_LAB_1_PERCEPTRON_H

#include "classifiers/interface/IClassifier.h"
#include "datasets/interface/IDataSetAccessor.h"
#include "neurons/interface/INeuron.h"

class Perceptron : public IClassifier
{
    IDataSetAccessor* dataSetAccessor;
    const INeuron* neuron;

    public:
        Perceptron(IDataSetAccessor* dataSetAccessor, const INeuron* neuron);
        ~Perceptron();

        void learn(int epochs) const override;

    private:
        double getDiscreteError(double output, double expectedOutput) const;
};


#endif //SN_LAB_1_PERCEPTRON_H

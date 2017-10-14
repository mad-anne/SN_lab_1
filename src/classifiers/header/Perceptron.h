#ifndef SN_LAB_1_PERCEPTRON_H
#define SN_LAB_1_PERCEPTRON_H

#include "classifiers/interface/IClassifier.h"
#include "datasets/interface/IDataSetAccessor.h"
#include "functions/interface/IActivationFunction.h"
#include "neurons/interface/INeuron.h"

class Perceptron : public IClassifier
{
    double alpha;

    IDataSetAccessor* dataSetAccessor;
    const INeuron* neuron;
    const IActivationFunction* function;
    double* weights;

    public:
        Perceptron(double alpha, IDataSetAccessor*, const INeuron*, const IActivationFunction*);
        ~Perceptron();

        void initRandomWeights(double zeroDeviation);
        void learn(int epochs) override;
        int predict(const IData* data) const;

    private:
        void learnEpoch();
        void updateWeights(double discreteError, const IData* data);
        double getDiscreteError(double output, double expectedOutput) const;
};


#endif //SN_LAB_1_PERCEPTRON_H

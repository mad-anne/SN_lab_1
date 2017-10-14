#ifndef SN_LAB_1_PERCEPTRON_H
#define SN_LAB_1_PERCEPTRON_H

#include "classifiers/interface/IClassifier.h"
#include "datasets/interface/IDataSetAccessor.h"
#include "neurons/interface/INeuron.h"

class Perceptron : public IClassifier
{
    double alpha;

    IDataSetAccessor* dataSetAccessor;
    const INeuron* neuron;
    double* weights;

    public:
        Perceptron(double alpha, IDataSetAccessor* dataSetAccessor, const INeuron* neuron);
        ~Perceptron();

        void learn(int epochs, double initWeightsDeviation) override;
        int predict(const IData* data) const;

    private:
        void learnEpoch();
        void updateWeights(double discreteError, const IData* data);

        double getDiscreteError(double output, double expectedOutput) const;
        void initRandomWeights(double max);
};


#endif //SN_LAB_1_PERCEPTRON_H

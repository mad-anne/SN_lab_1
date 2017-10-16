#ifndef SN_LAB_1_ADALINE_H
#define SN_LAB_1_ADALINE_H

#include "classifiers/interface/IScore.h"
#include "classifiers/interface/IClassifier.h"
#include "datasets/interface/IDataSetAccessor.h"
#include "functions/interface/IActivationFunction.h"
#include "neurons/interface/INeuron.h"


class Adaline : public IClassifier
{
    double alpha;
    const double* bias;
    const double minMSE;
    double* w0;

    IDataSetAccessor* dataSetAccessor;
    const INeuron* neuron;
    const IActivationFunction* function;
    double* weights;

    public:
        Adaline(double alpha, const double* bias, const double minMSE, IDataSetAccessor*, const INeuron*, const IActivationFunction*);
        ~Adaline();

        void initRandomWeights(double zeroDeviation);
        void learn(int epochs) override;
        int predict(const IData* data) const;
        const IScore* validate() override;

    private:
        double learnEpoch();
        void updateWeights(double discreteError, const IData* data);
        double getError(double output, double expectedOutput) const;
        void updateScore(IScore* score, int predictedLabel, int label);
};


#endif //SN_LAB_1_ADALINE_H

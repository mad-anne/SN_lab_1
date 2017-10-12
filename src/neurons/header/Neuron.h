#ifndef SN_LAB_1_NEURON_H
#define SN_LAB_1_NEURON_H

#include "functions/interface/IActivationFunction.h"
#include "neurons/interface/INeuron.h"

class Neuron : public INeuron
{
    const IActivationFunction* function;

    public:
        Neuron(const IActivationFunction* function);
        ~Neuron();

        double processData(const IData* data, double* weights) const override;

    private:
        double getNet(const double* inputs, const double* weights, const size_t dataSize) const;
};


#endif //SN_LAB_1_NEURON_H

#ifndef SN_LAB_1_NEURON_H
#define SN_LAB_1_NEURON_H

#include "neurons/interface/INeuron.h"

class Neuron : public INeuron
{
    int numberOfInputs;
    double alfa;

    public:
        Neuron(int numberOfInputs, double alfa);
        ~Neuron();

        double getDiscreteError(double output, double expectedOutput) const override;
        double getNet(double* inputs, double* weights) const override;
};


#endif //SN_LAB_1_NEURON_H

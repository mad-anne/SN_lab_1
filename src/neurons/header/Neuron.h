#ifndef SN_LAB_1_NEURON_H
#define SN_LAB_1_NEURON_H

#include "neurons/interface/INeuron.h"

class Neuron : public INeuron
{
    public:
        Neuron();
        ~Neuron();

        double getDiscreteError(double output, double expectedOutput) const override;
};


#endif //SN_LAB_1_NEURON_H

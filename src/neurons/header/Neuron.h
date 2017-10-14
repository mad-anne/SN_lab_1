#ifndef SN_LAB_1_NEURON_H
#define SN_LAB_1_NEURON_H

#include "neurons/interface/INeuron.h"

class Neuron : public INeuron
{
    public:
        Neuron();
        ~Neuron();

        double processData(const IData* data, double* weights, const double* bias, const double* w0) const override;

    private:
        double getNet(const double* inputs, const double* weights, const size_t dataSize, const double* bias, const double* w0) const;
};


#endif //SN_LAB_1_NEURON_H

#ifndef SN_LAB_1_INEURON_H
#define SN_LAB_1_INEURON_H

#include "datasets/interface/IData.h"

class INeuron
{
    public:
        ~INeuron() = default;

        virtual double processData(const IData* data, double* weights) const = 0;
};

#endif //SN_LAB_1_INEURON_H

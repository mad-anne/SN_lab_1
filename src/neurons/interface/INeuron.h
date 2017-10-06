#ifndef SN_LAB_1_INEURON_H
#define SN_LAB_1_INEURON_H

class INeuron
{
    public:
        ~INeuron() = default;

        virtual double getDiscreteError(double output, double expectedOutput) const = 0;
};

#endif //SN_LAB_1_INEURON_H

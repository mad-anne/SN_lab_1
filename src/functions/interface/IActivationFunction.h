#ifndef SN_LAB_1_IACTIVATIONFUNCTION_H
#define SN_LAB_1_IACTIVATIONFUNCTION_H

class IActivationFunction
{
    public:
        virtual ~IActivationFunction() = default;

        virtual double getOutput(double input) const = 0;
};

#endif //SN_LAB_1_IACTIVATIONFUNCTION_H

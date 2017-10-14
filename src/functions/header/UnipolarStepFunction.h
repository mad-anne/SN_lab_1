#ifndef SN_LAB_1_UNIPOLARSTEPFUNCTION_H
#define SN_LAB_1_UNIPOLARSTEPFUNCTION_H

#include "functions/interface/IActivationFunction.h"

class UnipolarStepFunction : public IActivationFunction
{
    public:
        UnipolarStepFunction();
        ~UnipolarStepFunction();

        double getOutput(double input) const override;
};


#endif //SN_LAB_1_UNIPOLARSTEPFUNCTION_H

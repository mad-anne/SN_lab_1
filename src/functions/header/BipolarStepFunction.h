#ifndef SN_LAB_1_BIPOLARSTEPFUNCTION_H
#define SN_LAB_1_BIPOLARSTEPFUNCTION_H

#include "functions/interface/IActivationFunction.h"

class BipolarStepFunction : public IActivationFunction
{
    public:
        BipolarStepFunction();
        ~BipolarStepFunction();

        double getOutput(double input) const override;
};


#endif //SN_LAB_1_BIPOLARSTEPFUNCTION_H

#ifndef SN_LAB_1_BIPOLARSTEPFUNCTION_H
#define SN_LAB_1_BIPOLARSTEPFUNCTION_H

#include "functions/interface/IActivationFunction.h"

class BipolarStepFunction : public IActivationFunction
{
    double theta;

    public:
        BipolarStepFunction(double theta);
        ~BipolarStepFunction();

        double getOutput(double input) const override;
};


#endif //SN_LAB_1_BIPOLARSTEPFUNCTION_H

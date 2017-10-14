#ifndef SN_LAB_1_PARAMETERSREADER_H
#define SN_LAB_1_PARAMETERSREADER_H

#include <map>
#include "files/interface/IParametersReader.h"

class ParametersReader : public IParametersReader
{
    std::map<std::string, double> parameters;

    public:
        ParametersReader();
        ~ParametersReader();

        void read(std::string fileName) override;
        void printParameters() const override;
        double getParameter(std::string name) const override;
};


#endif //SN_LAB_1_PARAMETERSREADER_H

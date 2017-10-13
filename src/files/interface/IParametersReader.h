#ifndef SN_LAB_1_IPARAMETERSREADER_H
#define SN_LAB_1_IPARAMETERSREADER_H

class IParametersReader
{
    public:
        virtual ~IParametersReader() = default;

        virtual void read() = 0;
        virtual void printParameters() const = 0;
        virtual double getParameter(std::string name) const = 0;
};

#endif //SN_LAB_1_IPARAMETERSREADER_H

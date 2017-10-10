#ifndef SN_LAB_1_IDATA_H
#define SN_LAB_1_IDATA_H

#include <cstdlib>

class IData
{
    public:
        ~IData() = default;

        virtual const double* getData() const = 0;
        virtual const int* getLabel() const = 0;
        virtual const size_t getDataSize() const = 0;
};

#endif //SN_LAB_1_IDATA_H

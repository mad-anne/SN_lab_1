#ifndef SN_LAB_1_DATA_H
#define SN_LAB_1_DATA_H

#include "datasets/interface/IData.h"

class Data : public IData
{
    const double* data;
    const int* label;
    const size_t dataSize;

    public:
        Data(const double* data, const int* label, const size_t dataSize);
        ~Data();

        const double* getData() const override;
        const int* getLabel() const override;
        const size_t getDataSize() const override;
};

#endif //SN_LAB_1_DATA_H
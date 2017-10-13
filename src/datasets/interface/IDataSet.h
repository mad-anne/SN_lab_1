#ifndef SN_LAB_1_IDATASET_H
#define SN_LAB_1_IDATASET_H

#include "datasets/interface/IData.h"

class IDataSet
{
    public:
        virtual ~IDataSet() = default;

        virtual const IData* getData(const int index) const = 0;
        virtual const size_t getDataSetSize() const = 0;
        virtual const size_t getDataSize() const = 0;
};

#endif //SN_LAB_1_IDATASET_H
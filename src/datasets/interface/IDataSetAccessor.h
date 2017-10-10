#ifndef SN_LAB_1_IDATASETACCESSOR_H
#define SN_LAB_1_IDATASETACCESSOR_H

#include "datasets/interface/IDataSet.h"

class IDataSetAccessor
{
    public:
        virtual ~IDataSetAccessor() = default;

        virtual void begin() = 0;
        virtual const IData* getNext() = 0;
        virtual void shuffle() = 0;
        virtual const IDataSet* getDataSet() const = 0;
};

#endif //SN_LAB_1_IDATASETACCESSOR_H

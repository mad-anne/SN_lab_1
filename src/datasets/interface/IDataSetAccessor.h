#ifndef SN_LAB_1_IDATASETACCESSOR_H
#define SN_LAB_1_IDATASETACCESSOR_H

#include <map>

#include "datasets/interface/IDataSet.h"

class IDataSetAccessor
{
    protected:
        const IDataSet* dataSet;

    private:
        IDataSetAccessor();

    public:
        IDataSetAccessor(const IDataSet* dataSet) : dataSet(dataSet) { };
        virtual ~IDataSetAccessor() = default;

        virtual void begin() = 0;
        virtual double* getNext() = 0;
        virtual void shuffle() = 0;
};

#endif //SN_LAB_1_IDATASETACCESSOR_H

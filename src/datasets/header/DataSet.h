#ifndef SN_LAB_1_DATASET_H
#define SN_LAB_1_DATASET_H

#include "datasets/interface/IDataSet.h"

class DataSet : public IDataSet
{
    std::vector<const IData*>* dataSet;
    const size_t dataSetSize;
    const size_t dataSize;

    public:
        DataSet(std::vector<const IData*>* dataSet, const size_t dataSize, const size_t dataSetSize);
        ~DataSet();

        const IData* getData(const int index) const override;
        const size_t getDataSetSize() const override;
        const size_t getDataSize() const override;

        void clearDataSet();
};


#endif //SN_LAB_1_DATASET_H

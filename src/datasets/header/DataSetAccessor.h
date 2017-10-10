#ifndef SN_LAB_1_DATASETACCESSOR_H
#define SN_LAB_1_DATASETACCESSOR_H

#include "datasets/interface/IDataSetAccessor.h"
#include "datasets/interface/IDataSet.h"

class DataSetAccessor : public IDataSetAccessor
{
    std::vector<int> dataIndexes;
    int currDataIndex;

    public:
        DataSetAccessor(const IDataSet*);
        ~DataSetAccessor();

        void shuffle() override;
        double* getNext() override;
        void begin() override;
};


#endif //SN_LAB_1_DATASETACCESSOR_H

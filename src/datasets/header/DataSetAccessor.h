#ifndef SN_LAB_1_DATASETACCESSOR_H
#define SN_LAB_1_DATASETACCESSOR_H

#include "datasets/interface/IDataSetAccessor.h"

class DataSetAccessor : public IDataSetAccessor
{
    const IDataSet* dataSet;
    std::vector<int> indexes;
    std::vector<int>::iterator it;

    public:
        DataSetAccessor(const IDataSet*);
        ~DataSetAccessor();

        void begin() override;
        const IData* getNext() override;
        void shuffle() override;

        const IDataSet* getDataSet() const override;
};


#endif //SN_LAB_1_DATASETACCESSOR_H

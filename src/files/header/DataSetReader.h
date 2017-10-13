#ifndef SN_LAB_1_DATASETREADER_H
#define SN_LAB_1_DATASETREADER_H

#include <string>

#include "datasets/header/DataSet.h"
#include "files/interface/IDataSetReader.h"

class DataSetReader : public IDataSetReader
{
    public:
        DataSetReader();
        ~DataSetReader();

        const IDataSet* readDataSet(std::string fileName, size_t dataSize) const override;
};


#endif //SN_LAB_1_DATASETREADER_H

#ifndef SN_LAB_1_DATASET_H
#define SN_LAB_1_DATASET_H

#include "datasets/interface/IDataSet.h"

class DataSet : public IDataSet
{
    double** inputs;
    int* labels;
    int numberOfInputs;
    int inputSize;

    public:
        DataSet(double** inputs, int* labels, int numberOfInputs, int inputSize);
        ~DataSet();

        double* getData(int index) const override;
        int getDataSetSize() const override;
        int getDataSize() const override;
};


#endif //SN_LAB_1_DATASET_H

#ifndef SN_LAB_1_DATASETACCESSOR_H
#define SN_LAB_1_DATASETACCESSOR_H

#include "datasets/interface/IDataSetAccessor.h"

class DataSetAccessor : public IDataSetAccessor
{
    const IDataSet* dataSet;
    std::vector<int> indexes;

    std::vector<int> trainingSetIndexes;
    std::vector<int> validatingSetIndexes;
    std::vector<int> testingSetIndexes;

    std::vector<int>::iterator trainingIt;
    std::vector<int>::iterator validatingIt;
    std::vector<int>::iterator testingIt;

    public:
        DataSetAccessor(const IDataSet*);
        ~DataSetAccessor();

        void splitDataSet(double trainingPart, double validatingPart, double testingPart) override;

        void trainingDataBegin() override;
        void validatingDataBegin() override;
        void testingDataBegin() override;

        const IData* getNextTrainingData() override;
        const IData* getNextValidatingData() override;
        const IData* getNextTestingData() override;

        void shuffleTrainingSet() override;

        const IDataSet* getDataSet() const override;
};


#endif //SN_LAB_1_DATASETACCESSOR_H

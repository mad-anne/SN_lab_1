#ifndef SN_LAB_1_IDATASETACCESSOR_H
#define SN_LAB_1_IDATASETACCESSOR_H

#include "datasets/interface/IDataSet.h"

class IDataSetAccessor
{
    public:
        virtual ~IDataSetAccessor() = default;

        virtual void splitDataSet(double trainingPart, double validatingPart, double testingPart) = 0;

        virtual void trainingDataBegin() = 0;
        virtual void validatingDataBegin() = 0;
        virtual void testingDataBegin() = 0;

        virtual const IData* getNextTrainingData() = 0;
        virtual const IData* getNextValidatingData() = 0;
        virtual const IData* getNextTestingData() = 0;

        virtual const size_t getTrainingDataSetSize() const = 0;
        virtual const size_t getValidatingDataSetSize() const = 0;
        virtual const size_t getTestingDataSetSize() const = 0;

        virtual void shuffleTrainingSet() = 0;

        virtual const IDataSet* getDataSet() const = 0;
};

#endif //SN_LAB_1_IDATASETACCESSOR_H

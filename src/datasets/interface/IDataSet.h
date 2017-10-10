#ifndef SN_LAB_1_IDATASET_H
#define SN_LAB_1_IDATASET_H

class IDataSet
{
    public:
        ~IDataSet() = default;

        virtual double* getData(int index) const = 0;
        virtual int getDataSetSize() const = 0;
        virtual int getDataSize() const = 0;
};

#endif //SN_LAB_1_IDATASET_H
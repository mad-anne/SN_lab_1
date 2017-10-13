#ifndef SN_LAB_1_IDATASETREADER_H
#define SN_LAB_1_IDATASETREADER_H

class IDataSetReader
{
    public:
        virtual ~IDataSetReader() = default;

        virtual const IDataSet* readDataSet(std::string fileName, size_t dataSize) const = 0;
};

#endif //SN_LAB_1_IDATASETREADER_H

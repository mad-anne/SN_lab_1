#ifndef SN_LAB_1_ISCORE_H
#define SN_LAB_1_ISCORE_H

class IScore
{
    public:
        virtual ~IScore() = default;

        virtual void setTruePositives(int truePositives) = 0;
        virtual void setTrueNegatives(int trueNegatives) = 0;
        virtual void setFalsePositives(int falsePositives) = 0;
        virtual void setFalseNegatives(int falseNegatives) = 0;
};

#endif //SN_LAB_1_ISCORE_H

#ifndef SN_LAB_1_ISCORE_H
#define SN_LAB_1_ISCORE_H

class IScore
{
    public:
        virtual ~IScore() = default;

        virtual void reset() = 0;

        virtual void addTruePositives(int truePositives) = 0;
        virtual void addTrueNegatives(int trueNegatives) = 0;
        virtual void addFalsePositives(int falsePositives) = 0;
        virtual void addFalseNegatives(int falseNegatives) = 0;

        virtual double getAccuracy() const = 0;
};

#endif //SN_LAB_1_ISCORE_H

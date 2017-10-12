#ifndef SN_LAB_1_ICLASSIFIER_H
#define SN_LAB_1_ICLASSIFIER_H

class IClassifier
{
    public:
        ~IClassifier() = default;

        virtual void learn(int epochs) const = 0;
};

#endif //SN_LAB_1_ICLASSIFIER_H

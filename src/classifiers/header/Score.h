#ifndef SN_LAB_1_SCORE_H
#define SN_LAB_1_SCORE_H

#include "classifiers/interface/IScore.h"

class Score : public IScore
{
    int truePositives;
    int trueNegatives;
    int falsePositives;
    int falseNegatives;

    public:
        Score();
        ~Score();

        void reset() override;

        void addTruePositives(int truePositives) override;
        void addTrueNegatives(int trueNegatives) override;
        void addFalsePositives(int falsePositives) override;
        void addFalseNegatives(int falseNegatives) override;

        double getAccuracy() const override;
};


#endif //SN_LAB_1_SCORE_H

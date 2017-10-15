#ifndef SN_LAB_1_SCORE_H
#define SN_LAB_1_SCORE_H

#include "classifiers/interface/IScore.h"

class Score : public IScore
{
    const size_t dataSetSize;

    int truePositives;
    int trueNegatives;
    int falsePositives;
    int falseNegatives;

    public:
        Score(const size_t dataSetSize);
        ~Score();

        void setTruePositives(int truePositives) override;
        void setTrueNegatives(int trueNegatives) override;
        void setFalsePositives(int falsePositives) override;
        void setFalseNegatives(int falseNegatives) override;
};


#endif //SN_LAB_1_SCORE_H

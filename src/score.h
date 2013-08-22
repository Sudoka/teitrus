#ifndef TEITRUS_SCORE_H_
#define TEITRUS_SCORE_H_

class Score
{
    private:
        int value;

    public:
        const float kScoreXPosition = ;
        const float kScoreYPosition = ;
        float x_position_, y_position_;
        Score();
        void increment(int);
        void show();
};

#endif

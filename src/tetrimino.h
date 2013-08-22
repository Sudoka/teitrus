#ifndef TEITRUS_TETRIMINO_H_
#define TEITRUS_TETRIMINO_H_
const int kBlockVelocity = 200;

class Tetrimino
{
    private:
        bool active_;
        int type_;
        float x_position_, y_position_;
        float x_velocity_, y_velocity_;
        float rotation_;
        std::string art_asset_;
        SDL_Surface * surface;

    public:

        const int kBlockWidth    = 50;
        const int kBlockHeight   = 50;
        const int kNumberOfTetroTypes = 7;
        const int kTetroI = 0;
        const int kTetroJ = 1;
        const int kTetroL = 2;
        const int kTetroO = 3;
        const int kTetroS = 4;
        const int kTetroT = 5;
        const int kTetroZ = 6;

        Tetrimino();
        ~Tetrimino();
        void move(int deltaTicks);
        void show(SDL_Surface *);
        void rotate(float);
};

#endif

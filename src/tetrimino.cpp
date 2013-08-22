#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Tetrimino.h"
#include "constants.h"

Tetrimino::Tetrimino()
{
    type_ = rand() % NUM_OF_PIECES;
    switch(type_) {
        case kTetroI: art_asset_ = AssetArtTetroI; break;
        case kTetroJ: art_asset_ = AssetArtTetroJ; break;
        case kTetroL: art_asset_ = AssetArtTetroL; break;
        case kTetroO: art_asset_ = AssetArtTetroO; break;
        case kTetroS: art_asset_ = AssetArtTetroS; break;
        case kTetroT: art_asset_ = AssetArtTetroT; break;
        case kTetroZ: art_asset_ = AssetArtTetroZ; break;
    }

    surface = load_image_alpha(art_asset_);

    //Initialize the offsets
    x_position_= 0;
    y_position_= 0;

    //Initialize the velocity
    x_velocity_ = 0;
    y_velocity_ = 0;

    rotation_ = 0;

    active_ = true;
}

void Tetrimino::move(int deltaTicks)
{
    //Move the dot left or right
    x_position_+= x_velocity_ * (deltaTicks / 1000.f);

    //If the dot went too far to the left
    if(x_position_< 0) {
        //Move back
        x_position_= 0;
    }
    //or the right
    else if(x_position_+ PIECE_WIDTH > SCREEN_WIDTH) {
        //Move back
        x_position_= SCREEN_WIDTH - PIECE_WIDTH;
    }

    //Move the dot up or down
    y_position_+= y_velocity_ * (deltaTicks / 1000.f);

    //If the dot went too far up
    if(y_position_< 0) {
        //Move back
        y_position_= 0;
    }
    //or down
    else if(y_position_+ PIECE_HEIGHT > SCREEN_HEIGHT) {
        //Move back
        y_position_= SCREEN_HEIGHT - PIECE_HEIGHT;
    }
}

void Tetrimino::show(SDL_Surface * screen)
{
    apply_surface(x_position_, y_position_, surface, screen);
}

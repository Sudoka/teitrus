////////////////////////////////////////////////////////////////////////////////
//  Header Files
////////////////////////////////////////////////////////////////////////////////

/* Standard Library */
#include <iostream>
#include <string>

/* Third Party Libraries */
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

/* Project Files */
#include "Tetrimino.h"
#include "Timer.h"
#include "constants.h"
#include "assets.h"

//The surfaces
SDL_Surface *screen = NULL;
SDL_Surface *game   = NULL;
SDL_Surface *loader = NULL;


bool init();
void clean_up();
SDL_Surface * load_image(std::string);
void apply_surface(int, int, SDL_Surface *, SDL_Surface *);

int main(int argc, char* args[])
{

    //The event structure
    SDL_Event event;

    //Quit flag
    bool quit = false;

    //The dot that will be used

    //Keeps track of time since last rendering
    Timer delta;

    //Initialize
    if(init() == false) {
        return 1;
    }

    //Start delta timer
    delta.start();

    //While the user hasn't quit
    while(quit == false) {
        //While there's events to handle
        while(SDL_PollEvent(&event)) {
            //Handle events for the dot
            //myDot.handle_input(event);

            //If the user has Xed out the window
            if(event.type == SDL_QUIT) {
                //Quit the program
                quit = true;
            }
        }

        //Move the dot
        //myDot.move(delta.get_ticks());

        //Restart delta timer
        delta.start();

        //Fill the screen white
        //SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

        //Show the dot on the screen
        //myDot.show(dot, screen);

        //Update the screen

        if(SDL_Flip(screen) == -1) {
            return 1;
        }
    }

    //Clean up
    clean_up();

    return 0;
}

SDL_Surface * load_image(std::string filename)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load(filename.c_str());

    //If the image loaded
    if(loadedImage != NULL) {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old surface
        SDL_FreeSurface(loadedImage);
    }

    //Return the optimized surface
    return optimizedImage;
}

SDL_Surface * load_image_alpha(std::string filename)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load(filename.c_str());

    //If the image loaded
    if(loadedImage != NULL) {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormatAlpha(loadedImage);

        //Free the old surface
        SDL_FreeSurface(loadedImage);
    }

    //Return the optimized surface
    return optimizedImage;
}

bool init()
{
    //Initialize all SDL subsystems
    if(SDL_Init( SDL_INIT_EVERYTHING) == -1) {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    //If there was an error in setting up the screen
    if(screen == NULL) {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption(APP_NAME.c_str(), NULL);

    game = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, RMASK, GMASK, BMASK, AMASK);

    if(game == NULL) {
        return false;
    }

    // Overlay
    loader = load_image(ASSET_ART_OVERLAY);
    apply_surface(0, 0, loader, game);

    // Title
    loader = load_image_alpha(ASSET_ART_TITLE);
    apply_surface(TITLE_X, TITLE_Y, loader, game);

    apply_surface(0, 0, game, screen);

    //If everything initialized fine
    return true;
}

void apply_surface(int x, int y, SDL_Surface * source, SDL_Surface * destination )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface(source, NULL, destination, &offset );
}

void handle_input(SDL_Event event)
{
    //If a key was pressed
    if(event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch(event.key.keysym.sym )
        {
            case SDLK_UP: yVel -= DOT_VEL; break;
            case SDLK_DOWN: yVel += DOT_VEL; break;
            case SDLK_LEFT: xVel -= DOT_VEL; break;
            case SDLK_RIGHT: xVel += DOT_VEL; break;
        }
    }
    //If a key was released
    else if(event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch(event.key.keysym.sym )
        {
            case SDLK_UP: yVel += DOT_VEL; break;
            case SDLK_DOWN: yVel -= DOT_VEL; break;
            case SDLK_LEFT: xVel += DOT_VEL; break;
            case SDLK_RIGHT: xVel -= DOT_VEL; break;
        }
    }
}

void clean_up()
{
    //Free the surface
    //SDL_FreeSurface(dot);

    //Quit SDL
    SDL_Quit();
}

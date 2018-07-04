#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool initSDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Could not be initialized! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow(
        "SDL Tutorial",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if(gWindow == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);

    return true;
}

bool loadMedia() {
    gHelloWorld = SDL_LoadBMP("resources/hello_world.bmp");
    if(gHelloWorld == NULL) {
        printf("Couldn't load media! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void destroySDL() {
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}


int main(int argc, char* argv[]) {
    bool sdlInitSuccess = initSDL();
    if(!sdlInitSuccess) {
        return -1;
    }

    bool loadMediaSuccess = loadMedia();
    if(!loadMediaSuccess) {
        return -1;
    }

    SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

    SDL_UpdateWindowSurface(gWindow);

    SDL_Delay(2000);

    destroySDL();

    return 0;
}

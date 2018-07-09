#include <string>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

enum Surfaces {
    SURFACE_ONE,
    SURFACE_TWO,
    SURFACE_THREE,
    SURFACE_FOUR,
};

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

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

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(gRenderer == NULL) {
        printf(
            "Renderer could not be created! SDL Error: %s\n",
            SDL_GetError()
        );
        return false;
    }

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        printf(
            "Could not initialize SDL Image extension! IMG Error: %s\n",
            IMG_GetError()
        );
    }

    return true;
}

SDL_Texture* loadTexture(std::string path) {
    SDL_Texture* texture = NULL;

    SDL_Surface* surface = IMG_Load(path.c_str());
    if(surface == NULL) {
        printf(
            "Could not load surface with image at path \"%s\". SDL_Error: %s\n",
            path.c_str(),
            SDL_GetError()
        );
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    if(texture == NULL) {
        printf(
            "Could not create texture from the loaded surface. SDL Error %s\n",
            SDL_GetError()
        );
        return NULL;
    }

    SDL_FreeSurface(surface);

    return texture;
}

bool loadMedia() {
    gTexture = loadTexture("resources/hello_world_1.png");
    if(gTexture == NULL) {
        printf("Failed to load the texture during media loading");
        return false;
    }

    return true;
}

void destroySDL() {
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
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

    SDL_Event event;
    bool isRunning = true;

    while(isRunning) {

        SDL_RenderClear(gRenderer);

        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

        SDL_RenderPresent(gRenderer);

        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT) {
                isRunning = false;
            }

            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
            }
        }
    }

    destroySDL();

    return 0;
}

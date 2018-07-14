#include <string>

#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

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

    return true;
}

void destroySDL() {
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}


int main(int argc, char* argv[]) {
    bool sdlInitSuccess = initSDL();
    if(!sdlInitSuccess) {
        return -1;
    }

    SDL_Event event;
    bool isRunning = true;

    while(isRunning) {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        SDL_Rect fillRect = {
            SCREEN_WIDTH / 4,
            SCREEN_HEIGHT / 4,
            SCREEN_WIDTH / 2,
            SCREEN_HEIGHT / 2,
        };

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &fillRect);

        SDL_Rect outlineRect = {
            SCREEN_WIDTH / 6,
            SCREEN_HEIGHT / 6,
            SCREEN_WIDTH * 2 / 3,
            SCREEN_HEIGHT * 2 / 3,
        };

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(gRenderer, &outlineRect);

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawLine(
            gRenderer,
            0,
            SCREEN_HEIGHT / 2,
            SCREEN_WIDTH,
            SCREEN_HEIGHT / 2
        );

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);

        for(int i = 0; i < SCREEN_HEIGHT; i += 4) {
            SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
        }

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

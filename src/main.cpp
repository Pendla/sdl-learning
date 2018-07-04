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
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gActiveSurface = NULL;
SDL_Surface* gSurfaces[4];

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

    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        printf(
            "Could not initialize SDL Image extension! IMG Error: %s\n",
            IMG_GetError()
        );
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);

    return true;
}

SDL_Surface* loadSurface(std::string path) {
    SDL_Surface* optimizedSurface;
    SDL_Surface* surface = IMG_Load(path.c_str());
    if(surface == NULL) {
        printf("Couldn't load surface. IMG Error: %s\n", IMG_GetError());
        return NULL;
    }

    optimizedSurface = SDL_ConvertSurface(surface, gScreenSurface->format, 0);
    if(optimizedSurface == NULL) {
        printf("Coulnd't optimize surface. SDL Error: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_FreeSurface(surface);

    return optimizedSurface;
}

bool loadMedia() {
    gSurfaces[SURFACE_ONE] = loadSurface("resources/hello_world_1.png");
    if(gSurfaces[SURFACE_ONE] == NULL) {
        printf("Failed to load SURFACE_ONE");
        return false;
    }

    gSurfaces[SURFACE_TWO] = loadSurface("resources/hello_world_2.png");
    if(gSurfaces[SURFACE_TWO] == NULL) {
        printf("Failed to load SURFACE_TWO");
        return false;
    }

    gSurfaces[SURFACE_THREE] = loadSurface("resources/hello_world_3.png");
    if(gSurfaces[SURFACE_THREE] == NULL) {
        printf("Failed to load SURFACE_THREE");
        return false;
    }

    gSurfaces[SURFACE_FOUR] = loadSurface("resources/hello_world_4.png");
    if(gSurfaces[SURFACE_FOUR] == NULL) {
        printf("Failed to load SURFACE_FOUR");
        return false;
    }

    gActiveSurface = gSurfaces[SURFACE_ONE];

    return true;
}

void destroySDL() {
    for(int i = 0; i < sizeof(gSurfaces) / sizeof(SDL_Surface*); i++) {
        SDL_FreeSurface(gSurfaces[i]);
        gSurfaces[i] = NULL;
    }

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

    SDL_Event event;
    bool isRunning = true;

    while(isRunning) {
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        SDL_BlitScaled(gActiveSurface, NULL, gScreenSurface, &stretchRect);

        SDL_UpdateWindowSurface(gWindow);

        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT) {
                isRunning = false;
            }

            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                } else if(event.key.keysym.sym == SDLK_LEFT) {
                    gActiveSurface = gSurfaces[SURFACE_ONE];
                } else if(event.key.keysym.sym == SDLK_UP) {
                    gActiveSurface = gSurfaces[SURFACE_TWO];
                } else if(event.key.keysym.sym == SDLK_RIGHT) {
                    gActiveSurface = gSurfaces[SURFACE_THREE];
                } else if(event.key.keysym.sym == SDLK_DOWN) {
                    gActiveSurface = gSurfaces[SURFACE_FOUR];
                }
            }
        }
    }

    destroySDL();

    return 0;
}

//Consertado
#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao iniciar SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Desenho SDL2_gfx",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int running = 1;
    SDL_Event event;

    while (running) {
        if (SDL_WaitEventTimeout(&event, 16)) {
            if (event.type == SDL_QUIT) running = 0;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        boxRGBA(renderer, 50, 50, 200, 150, 0, 0, 255, 255);

        filledCircleRGBA(renderer, 400, 300, 80, 255, 0, 0, 255);

        filledEllipseRGBA(renderer, 600, 200, 100, 50, 0, 200, 0, 255);

        thickLineRGBA(renderer, 100, 500, 700, 500, 8, 150, 0, 200, 255);

        Sint16 vx[5] = {300, 350, 400, 250, 200};
        Sint16 vy[5] = {400, 500, 400, 450, 500};
        filledPolygonRGBA(renderer, vx, vy, 5, 255, 255, 0, 255);

        Sint16 bx[4] = {100, 200, 300, 400};
        Sint16 by[4] = {100, 50, 150, 100};
        bezierRGBA(renderer, bx, by, 4, 3, 0, 180, 255, 255);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

int AUX_WaitEventTimeout(SDL_Event* evt, Uint32* ms) {
    if (*ms == 0) return 0;
    Uint32 start = SDL_GetTicks();
    int ret = SDL_WaitEventTimeout(evt, *ms);
    Uint32 elapsed = SDL_GetTicks() - start;
    if (elapsed >= *ms) *ms = 0;
    else *ms -= elapsed;
    return ret;
}

#define SQUARE_SIZE 50
#define DRAG_THRESHOLD 5

typedef enum { IDLE, CLICKED, DRAGGING } State;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Clique ou Arrasto",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect square = { 100, 100, SQUARE_SIZE, SQUARE_SIZE };
    int origX = square.x, origY = square.y;

    State state = IDLE;
    int clickX = 0, clickY = 0;
    bool running = true;
    SDL_Event evt;

    while (running) {
        Uint32 timeout = 16; // ~60 FPS
        while (AUX_WaitEventTimeout(&evt, &timeout)) {
            switch (evt.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (evt.button.button == SDL_BUTTON_LEFT &&
                        evt.button.x >= square.x && evt.button.x <= square.x + square.w &&
                        evt.button.y >= square.y && evt.button.y <= square.y + square.h) 
                    {
                        state = CLICKED;
                        clickX = evt.button.x;
                        clickY = evt.button.y;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (evt.button.button == SDL_BUTTON_LEFT) {
                        if (state == CLICKED) {
                            printf("Clique confirmado!\n");
                        }
                        state = IDLE;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    if (state == CLICKED) {
                        int dx = evt.motion.x - clickX;
                        int dy = evt.motion.y - clickY;
                        if (abs(dx) > DRAG_THRESHOLD || abs(dy) > DRAG_THRESHOLD) {
                            state = DRAGGING;
                        }
                    }
                    if (state == DRAGGING) {
                        square.x += evt.motion.xrel;
                        square.y += evt.motion.yrel;
                    }
                    break;
                case SDL_KEYDOWN:
                    if (evt.key.keysym.sym == SDLK_ESCAPE) {
                        if (state == CLICKED || state == DRAGGING) {
                            square.x = origX;
                            square.y = origY;
                            state = IDLE;
                            printf("Gesto cancelado!\n");
                        }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
        SDL_RenderFillRect(ren, &square);

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

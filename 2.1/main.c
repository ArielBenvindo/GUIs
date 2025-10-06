#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define MULTI_CLICK_TIMEOUT 250
#define AUX_WAIT_MS 16


int AUX_WaitEventTimeout(SDL_Event* evt, Uint32* ms) {
    if (*ms == 0) return 0;
    Uint32 inicio = SDL_GetTicks();
    int ret = SDL_WaitEventTimeout(evt, *ms);
    Uint32 fim = SDL_GetTicks();
    Uint32 decorrido = fim - inicio;
    if (decorrido >= *ms) *ms = 0;
    else *ms -= decorrido;
    return ret;
}

typedef struct {
    int active;
    int x, y;
    int count;
    Uint32 lastClickTime;
} MultiClickDetector;


void DrawCircle(SDL_Renderer *ren, int cx, int cy, int radius, SDL_Color color) {
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            if (dx*dx + dy*dy <= radius*radius) {
                SDL_RenderDrawPoint(ren, cx + dx, cy + dy);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("Múltiplos Cliques Animados",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       640, 480,
                                       SDL_WINDOW_SHOWN);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    int running = 1;
    SDL_Event e;
    MultiClickDetector detector = {0};

    SDL_Color colors[] = {
        {255,0,0,255},
        {0,0,255,255},
        {0,255,0,255},
        {255,128,0,255} 
    };

    while (running) {
        Uint32 waitTime = AUX_WAIT_MS;
        if (AUX_WaitEventTimeout(&e, &waitTime)) {
            if (e.type == SDL_QUIT) running = 0;

            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mx = e.button.x;
                int my = e.button.y;
                Uint32 now = SDL_GetTicks();

                if (!detector.active) {
                    detector.active = 1;
                    detector.x = mx;
                    detector.y = my;
                    detector.count = 1;
                    detector.lastClickTime = now;
                } else {
                    int dx = abs(mx - detector.x);
                    int dy = abs(my - detector.y);
                    if (dx <= 2 && dy <= 2 && (now - detector.lastClickTime) <= MULTI_CLICK_TIMEOUT) {
                        detector.count++;
                        detector.lastClickTime = now;
                    } else {

                        SDL_Event userEvent;
                        SDL_memset(&userEvent, 0, sizeof(userEvent));
                        userEvent.type = SDL_USEREVENT;
                        userEvent.user.code = detector.count;
                        SDL_PushEvent(&userEvent);

                        detector.x = mx;
                        detector.y = my;
                        detector.count = 1;
                        detector.lastClickTime = now;
                    }
                }
            }

            else if (e.type == SDL_MOUSEMOTION && detector.active) {
                int dx = abs(e.motion.x - detector.x);
                int dy = abs(e.motion.y - detector.y);
                if (dx > 2 || dy > 2) {
                    detector.active = 0;
                    detector.count = 0;
                }
            }

            else if (e.type == SDL_USEREVENT) {
                int n = e.user.code;
                SDL_Color color = (n <= 3) ? colors[n-1] : colors[3];
                int r = 10 + 5*(n-1); 

                int steps = 5;
                for (int s=0; s<steps; s++) {
                    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
                    SDL_RenderClear(ren);

                    int currentR = r + s*2;
                    DrawCircle(ren, detector.x, detector.y, currentR, color);

                    SDL_RenderPresent(ren);
                    SDL_Delay(30);
                }
            }
        }

        if (detector.active && (SDL_GetTicks() - detector.lastClickTime) > MULTI_CLICK_TIMEOUT) {
            SDL_Event userEvent;
            SDL_memset(&userEvent, 0, sizeof(userEvent));
            userEvent.type = SDL_USEREVENT;
            userEvent.user.code = detector.count;
            SDL_PushEvent(&userEvent);

            detector.active = 0;
            detector.count = 0;
        }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

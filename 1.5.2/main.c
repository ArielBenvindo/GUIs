#include <SDL.h>
#include <stdio.h>


// Função auxiliar
int AUX_WaitEventTimeout(SDL_Event* evt, Uint32* ms) {
    if (*ms == 0) {
        return 0;
    }

    Uint32 inicio = SDL_GetTicks();

    int ret = SDL_WaitEventTimeout(evt, *ms);

    Uint32 fim = SDL_GetTicks();
    Uint32 decorrido = fim - inicio;

    if (decorrido >= *ms) {
        *ms = 0;
    } else {
        *ms -= decorrido;
    }
    return ret;
}

int main (int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Três Retângulos",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    SDL_Rect rectTempo = { 20, 20, 20, 20 };
    double posTempoX = rectTempo.x;
    const double velocidade = 100.0;

    SDL_Rect rectTeclado = { 100, 50, 20, 20 };
    SDL_Rect rectMouse   = { 200, 100, 20, 20 };

    SDL_Event evt;
    int running = 1;
    Uint32 lastTick = SDL_GetTicks();

    while (running) {
        Uint32 now = SDL_GetTicks();
        Uint32 delta = now - lastTick;
        lastTick = now;

        posTempoX += velocidade * (delta / 1000.0);
        if (posTempoX > 400) posTempoX = -rectTempo.w;
        rectTempo.x = (int)posTempoX;

        SDL_SetRenderDrawColor(ren, 255,255,255,255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255,0,0,255);
        SDL_RenderFillRect(ren, &rectTempo);

        SDL_SetRenderDrawColor(ren, 0,255,0,255);
        SDL_RenderFillRect(ren, &rectTeclado);

        SDL_SetRenderDrawColor(ren, 0,0,255,255);
        SDL_RenderFillRect(ren, &rectMouse);

        SDL_RenderPresent(ren);

        Uint32 ms = 16;
        while (AUX_WaitEventTimeout(&evt, &ms)) {
            if (evt.type == SDL_QUIT) running = 0;

            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:    rectTeclado.y -= 5; break;
                    case SDLK_DOWN:  rectTeclado.y += 5; break;
                    case SDLK_LEFT:  rectTeclado.x -= 5; break;
                    case SDLK_RIGHT: rectTeclado.x += 5; break;
                }
            }

            if (evt.type == SDL_MOUSEMOTION) {
                rectMouse.x = evt.motion.x;
                rectMouse.y = evt.motion.y;
            }
        }
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

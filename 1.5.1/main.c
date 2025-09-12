//Consertado, usa agora só o SDL_WaitEventTimeout

#include <SDL.h>
#include <stdio.h>

int main (int argc, char* args[])
{
    /* INICIALIZAÇÃO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Três Retângulos",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    SDL_Rect rectTempo = { 20, 20, 20, 20 };
    SDL_Rect rectTeclado = { 100, 50, 20, 20 };
    SDL_Rect rectMouse = { 200, 100, 20, 20 };

    /* EXECUÇÃO */
    SDL_Event evt;
    int running = 1;

    while (running) {
        if (SDL_WaitEventTimeout(&evt, 16)) {
            if (evt.type == SDL_QUIT) {
                running = 0;
            }

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

        rectTempo.x += 1;
        if (rectTempo.x > 400) rectTempo.x = -rectTempo.w;

        SDL_SetRenderDrawColor(ren, 255,255,255,255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 255,0,0,255);
        SDL_RenderFillRect(ren, &rectTempo);

        SDL_SetRenderDrawColor(ren, 0,255,0,255);
        SDL_RenderFillRect(ren, &rectTeclado);

        SDL_SetRenderDrawColor(ren, 0,0,255,255);
        SDL_RenderFillRect(ren, &rectMouse);

        SDL_RenderPresent(ren);
    }

    /* FINALIZAÇÃO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

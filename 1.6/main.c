#include <SDL.h>
#include <stdio.h>

#define WIDTH 400
#define HEIGHT 200
#define FINISH_LINE 350
#define WAIT_TIME 3000  // 3 segundos

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Corrida SDL",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    SDL_Rect rectTempo   = { 20, 20, 20, 20 };
    SDL_Rect rectTeclado = { 20, 60, 20, 20 };
    SDL_Rect rectMouse   = { 20, 100, 20, 20 };

    int tempoParado = 0, tecladoParado = 0, mouseParado = 0;
    const char* vencedor = NULL;
    Uint32 waitStart = 0; 


    SDL_Event evt;
    int running = 1;

    while (running) {
        if (SDL_WaitEventTimeout(&evt, 16)) {
            if (evt.type == SDL_QUIT) {
                running = 0;
            }

            if (!tecladoParado && evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_LEFT:  rectTeclado.x -= 5; break;
                    case SDLK_RIGHT: rectTeclado.x += 5; break;
                }
            }

            if (!mouseParado && evt.type == SDL_MOUSEMOTION) {
                rectMouse.x = evt.motion.x;
            }
        }

        if (!tempoParado) rectTempo.x += 1;

        if (!tempoParado   && rectTempo.x + rectTempo.w >= FINISH_LINE) {
            tempoParado = 1;
            if (!vencedor) vencedor = "Vermelho (Tempo)";
        }
        if (!tecladoParado && rectTeclado.x + rectTeclado.w >= FINISH_LINE) {
            tecladoParado = 1;
            if (!vencedor) vencedor = "Verde (Teclado)";
        }
        if (!mouseParado   && rectMouse.x + rectMouse.w >= FINISH_LINE) {
            mouseParado = 1;
            if (!vencedor) vencedor = "Azul (Mouse)";
        }

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderDrawLine(ren, FINISH_LINE, 0, FINISH_LINE, HEIGHT);

        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
        SDL_RenderFillRect(ren, &rectTempo);

        SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
        SDL_RenderFillRect(ren, &rectTeclado);

        SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
        SDL_RenderFillRect(ren, &rectMouse);

        SDL_RenderPresent(ren);

        if (tempoParado && tecladoParado && mouseParado && waitStart == 0) {
            printf("Vencedor: %s\n", vencedor);
            waitStart = SDL_GetTicks();
        }

        if (waitStart > 0 && SDL_GetTicks() - waitStart >= WAIT_TIME) {
            rectTempo.x = rectTeclado.x = rectMouse.x = 20;
            tempoParado = tecladoParado = mouseParado = 0;
            vencedor = NULL;
            waitStart = 0;
        }
    }

    /* FINALIZAÇÃO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

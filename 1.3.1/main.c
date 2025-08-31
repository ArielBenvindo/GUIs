#include <SDL.h>

int main(int argc, char* args[])
{
    /* INICIALIZAÇÃO */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Quadrado em Movimento",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       400, 300,
                                       SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    /* VARIÁVEIS DO QUADRADO */
    SDL_Rect r = {40, 20, 20, 20};  // posição inicial
    int phase = 0;                  // controla direção
    int runs = 0;                   // quantas voltas completas

    /* LOOP PRINCIPAL */
    SDL_Event event;
    int running = 1;
    while (running) {
        /* TRATA EVENTOS */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
        }

        /* LIMPAR TELA */
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // branco
        SDL_RenderClear(ren);

        /* DESENHAR QUADRADO */
        SDL_SetRenderDrawColor(ren, 0, 0, 255, 255); // azul
        SDL_RenderFillRect(ren, &r);

        SDL_RenderPresent(ren);
        SDL_Delay(16); // ~60 FPS

        /* LÓGICA DO MOVIMENTO */
        if (r.x < 300 && phase == 0) {
            r.x += 2;
        } else if (phase == 0) {
            phase = 1;
        } else if (phase == 1 && r.y < 200) {
            r.y += 2;
        } else if (phase == 1) {
            phase = 2;
        } else if (phase == 2 && r.x > 40) {
            r.x -= 2;
        } else if (phase == 2) {
            phase = 3;
        } else if (phase == 3 && r.y > 20) {
            r.y -= 2;
        } else if (phase == 3) {
            phase = 0;
            runs++;
            if (runs >= 2) running = 0; // para depois de 2 voltas
        }
    }

    /* FINALIZAÇÃO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

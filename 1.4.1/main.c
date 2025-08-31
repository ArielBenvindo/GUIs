#include <SDL.h>
#include <stdio.h>

int main (int argc, char* args[])
{
    /* INICIALIZAÇÃO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         200, 100, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* Retângulo que se move */
    SDL_Rect r = { 40,20, 10,10 };

    /* Retângulos fixos */
    SDL_Rect rects[10];
    SDL_Color colors[10] = {
        {255,0,0,255}, {0,255,0,255}, {0,0,255,255},
        {255,255,0,255}, {255,0,255,255}, {0,255,255,255},
        {128,0,128,255}, {255,128,0,255}, {128,128,128,255},
        {0,128,255,255}
    };
    int rectCount = 0;

    /* EXECUÇÃO */
    SDL_Event evt;
    int running = 1;
    while (running) {
        /* Cor de fundo */
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(ren);

        /* Desenha retângulos fixos */
        for (int i = 0; i < rectCount; i++) {
            SDL_SetRenderDrawColor(ren, colors[i].r, colors[i].g, colors[i].b, 255);
            SDL_RenderFillRect(ren, &rects[i]);
        }

        /* Desenha retângulo móvel */
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0xFF);
        SDL_RenderFillRect(ren, &r);

        SDL_RenderPresent(ren);

        /* Espera evento */
        SDL_WaitEvent(&evt);
        if (evt.type == SDL_KEYDOWN) {
            switch (evt.key.keysym.sym) {
                case SDLK_UP:
                    r.y -= 5;
                    break;
                case SDLK_DOWN:
                    r.y += 5;
                    break;
                case SDLK_LEFT:
                    r.x -= 5;
                    break;
                case SDLK_RIGHT:
                    r.x += 5;
                    break;
            }

            /* Mantém dentro da tela */
            if (r.x < 0) r.x = 0;
            if (r.y < 0) r.y = 0;
            if (r.x + r.w > 200) r.x = 200 - r.w;
            if (r.y + r.h > 100) r.y = 100 - r.h;
        }

        /* Adiciona retângulo fixo com clique do mouse */
        if (evt.type == SDL_MOUSEBUTTONDOWN) {
            if (rectCount < 10) {
                rects[rectCount].x = evt.button.x;
                rects[rectCount].y = evt.button.y;
                rects[rectCount].w = 15;
                rects[rectCount].h = 15;
                rectCount++;
            }
        }

        /* Fecha a aplicação */
        if (evt.type == SDL_QUIT) running = 0;
    }

    /* FINALIZAÇÃO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

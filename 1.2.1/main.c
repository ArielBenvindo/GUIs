//Consertado
#include <SDL.h>

int main(int argc, char* args[])
{
    /* INICIALIZAÇÃO */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Desenho Colorido",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       400, 300,
                                       SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);

    SDL_Rect r1 = {50, 50, 100, 60};
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255)
    SDL_RenderFillRect(ren, &r1);

    SDL_Rect r2 = {200, 30, 80, 120};
    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
    SDL_RenderFillRect(ren, &r2);

    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
    SDL_RenderDrawLine(ren, 0, 0, 400, 300);
    SDL_RenderDrawLine(ren, 0, 300, 400, 0);

    SDL_SetRenderDrawColor(ren, 255, 0, 255, 255);
    SDL_RenderDrawPoint(ren, 100, 200);
    SDL_RenderDrawPoint(ren, 150, 220);
    SDL_RenderDrawPoint(ren, 180, 250);

    SDL_RenderPresent(ren);

    SDL_Event event;
    int running = 1;
    while (running) {
        if (SDL_WaitEventTimeout(&event, 16)) {
            if (event.type == SDL_QUIT) running = 0;
        }
    }

    /* FINALIZAÇÃO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

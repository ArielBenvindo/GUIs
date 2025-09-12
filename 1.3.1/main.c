//Consertado
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

    SDL_Rect r = {40, 20, 20, 20}; 
    int phase = 0;               
    int runs = 0;        

    SDL_Event event;
    int running = 1;
    
    while (running) {

        if (SDL_WaitEventTimeout(&event, 16)) {
            if (event.type == SDL_QUIT) running = 0;
        }

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);


        SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
        SDL_RenderFillRect(ren, &r);

        SDL_RenderPresent(ren);

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
            if (runs >= 2) running = 0;
        }
    }

    /* FINALIZAÇÃO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}

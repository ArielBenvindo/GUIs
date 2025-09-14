#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main (int argc, char* args[])
{
    /* INICIALIZAÇÃO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* win = SDL_CreateWindow("Recorte",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         400, 200, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* img = IMG_LoadTexture(ren, "player-0.png");
    assert(img != NULL);

    int numFrames = 6;        
    int frameW = 16;         
    int frameH = 16;

    int frame = 0;
    int x = -frameW;

    /* EXECUÇÃO */
    int running = 1;
    while (running) {
        SDL_Event e;

        if (SDL_WaitEventTimeout(&e, 150)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ren);

        SDL_Rect r = { x, 50, frameW * 4, frameH * 4 };

        SDL_Rect c = { frame * frameW, 0, frameW, frameH };

        SDL_RenderCopy(ren, img, &c, &r);
        SDL_RenderPresent(ren);

        x = (x + 10) % 400;
        frame = (frame + 1) % numFrames;
    }

    /* FINALIZAÇÃO */
    SDL_DestroyTexture(img);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

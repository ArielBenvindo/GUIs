#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <assert.h>

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

int main(int argc, char* args[])
{
    /* INICIALIZAÇÃO */
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* win = SDL_CreateWindow("Sprite Animada em Movimento (Eventos)",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       400, 300,
                                       SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* sprite = IMG_LoadTexture(ren, "player-0.png");
    assert(sprite != NULL);

    int numFrames = 6;
    int frameW = 16;
    int frameH = 16;
    int frameAtual = 0;

    Uint32 tempoFrame = 100;
    Uint32 tempoAteProximoFrame = tempoFrame;

    SDL_Rect r = {40, 20, frameW * 4, frameH * 4};
    int phase = 0;
    int runs = 0;

    /* Loop principal */
    SDL_Event event;
    int running = 1;
    const Uint32 loopDelay = 16;

    while (running) {
        Uint32 tempoRestante = loopDelay;

        while (AUX_WaitEventTimeout(&event, &tempoRestante)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } 
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
                if (phase == 0) phase = 2;
                else if (phase == 1) phase = 3;
                else if (phase == 2) phase = 0;
                else if (phase == 3) phase = 1;
            } 
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a) {
                if (phase == 2) phase = 0;
                else if (phase == 3) phase = 1;
                else if (phase == 0) phase = 2;
                else if (phase == 1) phase = 3;
            }
        }

        if (r.x < 300 && phase == 0) {
            r.x += 1;
        } else if (phase == 0) {
            phase = 1;
        } else if (phase == 1 && r.y < 200) {
            r.y += 1;
        } else if (phase == 1) {
            phase = 2;
        } else if (phase == 2 && r.x > 40) {
            r.x -= 1;
        } else if (phase == 2) {
            phase = 3;
        } else if (phase == 3 && r.y > 20) {
            r.y -= 1;
        } else if (phase == 3) {
            phase = 0;
            runs++;
            if (runs >= 2) running = 0;
        }

        if (tempoAteProximoFrame <= loopDelay) {
            frameAtual = (frameAtual + 1) % numFrames;
            tempoAteProximoFrame = tempoFrame;
        } else {
            tempoAteProximoFrame -= loopDelay;
        }

        /* Renderização */
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

        SDL_Rect src = { frameAtual * frameW, 0, frameW, frameH };
        SDL_RenderCopy(ren, sprite, &src, &r);

        SDL_RenderPresent(ren);
    }

    /* FINALIZAÇÃO */
    SDL_DestroyTexture(sprite);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <texturelist.h>
#include <texture.h>
#define TEXTURE_W 32
#define TEXTURE_H 32

int main(int argc, char* argv[])
{
    char probapalya[7][7] =
    {
        {1,1,1,1,1,1,1},
        {1,0,0,0,0,0,1},
        {1,0,0,0,2,0,1},
        {1,0,0,0,2,0,1},
        {1,0,0,0,2,0,1},
        {1,0,0,0,0,0,1},
        {1,1,1,1,1,1,1}
    };
    SDL_Window* window=nullptr;
    SDL_Renderer* renderer=nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL not initialized: " << SDL_GetError();
    }
    else
    {
        std::cout << "SDL initialized";
    }

    window = SDL_CreateWindow("MOSZE test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    bool gameIsRunning = true;
    while(gameIsRunning)
    {
        SDL_Event event;
        // event loop, PollEvent-el végig megyünk minden egyes event-en
        // ezekre különböző módon írunk "válaszokat"
        while(SDL_PollEvent(&event))
        {
            // SDL_QUIT = sarokban lévő X-el bezárás
            if(event.type == SDL_QUIT)
            {
                gameIsRunning= false;
            }
            // SDL_KEYDOWN = bármilyen billentyű lenyomása
            if(event.type == SDL_KEYDOWN)
            {
                // sima próba 0-ra
                if(event.key.keysym.sym == SDLK_0)
                {
                    std::cout << "0 megnyomva";
                }
            }
        }

        //az adott színt az adott rendererre fogja váltani
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        //jelenlegi renderer kirajzolása
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
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
        // Start our event loop
        while(SDL_PollEvent(&event))
        {
            // Handle each specific event
            if(event.type == SDL_QUIT)
            {
                gameIsRunning= false;
            }
        }
    }
    
    SDL_DestroyWindow(window);
    return 0;
}
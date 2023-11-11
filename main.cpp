#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <stdio.h>
#include <string>
#include <iostream>
#define TEXTURE_W 32
#define TEXTURE_H 32

//egy class különböző képek létrehozásához
class CreateTexture
{
    //Rect egy négyzetet hoz létre, amelyre kell helyezni a texture-t

    SDL_Rect rectangle;
    SDL_Texture* texture;

    public:
    //konstruktor
    CreateTexture(SDL_Renderer*& renderer, std::string PathToTexture, int xPosC, int yPosC)
    {
        //ez a rectangle, azaz a négyzet inicializálása
        //x és y a bal felső sarok koordinátái
        //w és h rendre width és height, azaz a dimenziók

        this->rectangle.x = xPosC;
        this->rectangle.y = yPosC;
        this->rectangle.w = TEXTURE_W;
        this->rectangle.h = TEXTURE_H;

        //a surface tárolja a pixel információkat
        //ebbe egy bmp formátumú képet töltünk be
        //miután át lett másolva ez a "texture"-re
        //a freesurface-el eltöröljük

        SDL_Surface* surface = SDL_LoadBMP(PathToTexture.c_str());
        texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_FreeSurface(surface);
    }
    //destruktor
    ~CreateTexture()
    {
        SDL_DestroyTexture(texture);
    }


    //a rendercopy az adott rendererre másolja át a texture-t
    //a NULL azt jelöli, hogy az egész részét másoljuk a képnek
    //a &rectangle pedig, hogy melyik rect-re/négyzetre másoljuk
    void RenderTexture(SDL_Renderer*& renderer)
    {
        SDL_RenderCopy(renderer, texture, NULL, &rectangle);
    }
};


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
    
    CreateTexture proba1(renderer, "./assets/red.bmp",40,40);

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
        proba1.RenderTexture(renderer);

        //jelenlegi renderer kirajzolása
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
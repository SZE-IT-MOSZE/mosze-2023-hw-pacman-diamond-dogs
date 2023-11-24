#define SDL_MAIN_HANDLED
#include <iostream>
#include <enemy.hpp>
#include <vector>
#include <cmath>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <windows.h>

// from SDL
#include <SDL.h>

const int SCREEN_W = 640;
const int SCREEN_H = 512;
const int TEXTURE_W = 32;
const int TEXTURE_H = 32;
const int ScreenOffsetX = SCREEN_W / 2;
const int ScreenOffsetY = SCREEN_H / 2;

int main(int argc, char* argv[])
{
    ShowWindow (GetConsoleWindow(), SW_HIDE);

    SDL_Window* window=nullptr;
    SDL_Renderer* renderer=nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cerr << "SDL not initialized: " << SDL_GetError ();


    window = SDL_CreateWindow("MOSZE test",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_W,
                              SCREEN_H,
                              SDL_WINDOW_SHOWN
                              );

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);


    int charXPos = 4;
    int charYPos = 4;

    int probapalya[15][15] =
    {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
        {0,0,0,1,2,2,2,2,2,2,2,1,0,0,0},
        {0,0,1,1,2,2,2,1,1,2,2,1,1,1,0},
        {0,0,1,2,2,2,2,2,2,2,2,2,2,1,0},
        {1,1,1,2,2,2,2,2,2,2,2,2,2,1,0},
        {1,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
        {1,2,2,2,2,2,2,1,1,1,1,2,2,1,0},
        {1,1,1,2,2,2,2,2,2,2,2,2,2,1,0},
        {0,0,1,2,2,2,2,2,2,2,2,2,2,1,0},
        {0,0,1,2,1,1,2,2,2,1,2,2,2,1,0},
        {0,0,1,2,2,2,2,2,2,1,2,2,1,1,0},
        {0,0,1,2,2,2,2,2,2,2,2,2,1,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,2}
    };

    SDL_Rect rectmap[40][40];
    for (int x=0; x < 40; x++)
        for (int y=0; y < 40; y++) {
            rectmap[x][y].x = x*32;
            rectmap[x][y].y = y*32;
            rectmap[x][y].w = 32;
            rectmap[x][y].h = 32;
        }
    
    std::vector<Entity*> EntityList;
    std::vector<Enemy*> EnemyList;
    EntityList.push_back(new Enemy(renderer,"./assets/purple.bmp",6,6,3));
    EntityList.push_back(new Entity(renderer,"./assets/blue.bmp",5,5));
    EntityList.push_back(new Entity(renderer,"./assets/blue.bmp",6,7));
    EntityList.push_back(new Entity(renderer,"./assets/blue.bmp",10,10));

    SDL_Rect character;
    character.x = ScreenOffsetX;
    character.y = ScreenOffsetY;
    character.w = 32;
    character.h = 32;

    SDL_Surface* surface1 = SDL_LoadBMP("./assets/red.bmp");
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer,surface1);

    SDL_Surface* surface2 = SDL_LoadBMP("./assets/green.bmp");
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer,surface2);

    SDL_Surface* surface3 = SDL_LoadBMP("./assets/blue.bmp");
    SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer,surface3);

    SDL_Surface* surface4 = SDL_LoadBMP("./assets/purple.bmp");
    SDL_Texture* texture4 = SDL_CreateTextureFromSurface(renderer,surface4);

    bool gameIsRunning = true;
    SDL_Event event;

    while(gameIsRunning) {                       // event loop, PollEvent-el végig megyünk minden egyes event-en
        while(SDL_PollEvent(&event)) {           // ezekre különböző módon írunk "válaszokat"
            if(event.type == SDL_QUIT) {         // SDL_QUIT = sarokban lévő X-el bezárás
                gameIsRunning = false;
                break;
            }
            if(event.type == SDL_KEYDOWN) {     // SDL_KEYDOWN = bármilyen billentyű lenyomása
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        if (probapalya[charYPos - 1][charXPos] == 1) {
                            std::cout << "falnak utkoztem, a fal koordinatai:";
                            std::cout << charXPos << " " << charYPos-1 << std::endl;
                            break;
                        } else {
                            charYPos--;
                            std::cout << "leptem, a jelenlegi koordinataim: " << charXPos << " " << charYPos << std::endl;
                            break;
                        }

                    case SDLK_DOWN:
                        if (probapalya[charYPos + 1][charXPos] == 1) {
                            std::cout << "falnak utkoztem, a fal koordinatai:";
                            std::cout << charXPos << " " << charYPos+1 << std::endl;
                            break;
                        } else {
                            charYPos++;
                            std::cout << "leptem, a jelenlegi koordinataim: " << charXPos << " " << charYPos << std::endl;
                            break;
                        }

                    case SDLK_RIGHT:
                        if (probapalya[charYPos][charXPos + 1] == 1) {
                            std::cout << "falnak utkoztem, a fal koordinatai:";
                            std::cout << charXPos+1 << " " << charYPos << std::endl;
                            break;
                        } else {
                            charXPos++;
                            std::cout << "leptem, a jelenlegi koordinataim: " << charXPos << " " << charYPos << std::endl;
                            break;
                        }

                    case SDLK_LEFT:
                        if (probapalya[charYPos][charXPos - 1] == 1) {
                            std::cout << "falnak utkoztem, a fal koordinatai:";
                            std::cout << charXPos-1 << " " << charYPos << std::endl;
                            break;
                        } else {
                            charXPos--;
                            std::cout << "leptem, a jelenlegi koordinataim: " << charXPos << " " << charYPos << std::endl;
                            break;
                        }

                    default:
                        continue;
                }// switch
            }// if (event.type...
        }// while (poll event...

        //az adott színt az adott rendererre fogja váltani
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for (int x = 0; x < 15; x++) {
            for (int y = 0; y < 15; y++) {
                switch (probapalya[y][x]) {
                    case 1:
                        SDL_RenderCopy(renderer,
                                       texture1,
                                       NULL,
                                       &rectmap[x + (ScreenOffsetX/TEXTURE_W) - charXPos][y + (ScreenOffsetY/TEXTURE_H) - charYPos]
                                       );
                        break;

                    case 2:
                        SDL_RenderCopy(renderer,
                                       texture2,
                                       NULL,
                                       &rectmap[x + (ScreenOffsetX/TEXTURE_W) - charXPos][y + (ScreenOffsetY/TEXTURE_H) - charYPos]
                                       );
                        break;

                    default:
                        continue;
                }// switch
            }//for (y...
        }// for (x...

        bool inCombat = 0;

        auto it1 = EnemyList.begin();
        while (it1 != EnemyList.end()){
            (*it1)->UpdateEntityPos(charXPos,charYPos);
            (*it1)->RenderEntity(renderer);

            if(((*it1)->GetXPos() == charXPos && std::abs((*it1)->GetYPos()-charYPos)==1) || 
              ((*it1)->GetXPos() == charXPos && std::abs((*it1)->GetYPos()-charYPos)==1)){
                inCombat = 1;
                while(inCombat){
                    std::cout << "combatban vagyok" << std::endl;
                    if(event.type == SDL_KEYDOWN){
                        if(event.key.keysym.sym == SDLK_RETURN){
                            (*it1)->SetHealth((*it1)->GetHealth()-1);
                        }
                        if((*it1)->GetHealth() == 0){
                            inCombat = 0;
                        }
                    }
                }
            } else {
                ++it1;
            }
        }

        //egyelőre automatikusan felvesszük
        //az entityket entitylistből
        auto it = EntityList.begin();
        while (it != EntityList.end()){
            (*it)->UpdateEntityPos(charXPos,charYPos);
            (*it)->RenderEntity(renderer);

            if((*it)->GetXPos() == charXPos && (*it)->GetYPos() == charYPos){
                it = EntityList.erase(it);
            } else {
                ++it;
            }
        }
        
        SDL_RenderCopy(renderer, texture3, NULL, &character); // karakter helyzete
        SDL_RenderPresent(renderer);            // jelenlegi render kirajzolás
    }// while (gameIsRunning)
    

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

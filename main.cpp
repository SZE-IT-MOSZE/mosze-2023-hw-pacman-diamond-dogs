#define SDL_MAIN_HANDLED
#include <iostream>
#include <entity.hpp>
#include <enemy.hpp>
#include <player.hpp>
#include <vector>
#include <cmath>
#include <algorithm>
#include <SDL_render.h>
#include <SDL_surface.h>

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
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window=nullptr;
    SDL_Renderer* renderer=nullptr;

    Player MainPlayer(renderer,"./assets/purple.bmp",4,4,10);
    
    window = SDL_CreateWindow("MOSZE test",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_W,
                              SCREEN_H,
                              SDL_WINDOW_SHOWN
                              );

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

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
    EnemyList.push_back(new Enemy(renderer,"./assets/purple.bmp",6,6,3,"orc"));
    EnemyList.push_back(new Enemy(renderer,"./assets/purple.bmp",8,8,3,"orc"));
    EntityList.push_back(new Entity(renderer,"./assets/blue.bmp",5,5));
    EntityList.push_back(new Entity(renderer,"./assets/blue.bmp",6,7));
    EntityList.push_back(new Entity(renderer,"./assets/blue.bmp",10,10));

    SDL_Rect character;
    character.x = ScreenOffsetX;
    character.y = ScreenOffsetY;
    character.w = 32;
    character.h = 32;

    SDL_Surface* surface0 = SDL_LoadBMP("./assets/black.bmp");
    SDL_Texture* texture0 = SDL_CreateTextureFromSurface(renderer,surface0);

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
    bool inCombat = 0;

    while(gameIsRunning) {                       // event loop, PollEvent-el végig megyünk minden egyes event-en
        while(SDL_PollEvent(&event)) {           // ezekre különböző módon írunk "válaszokat"
            if(event.type == SDL_QUIT) {         // SDL_QUIT = sarokban lévő X-el bezárás
                gameIsRunning = false;
                break;
            }
            if(event.type == SDL_KEYDOWN) {     // SDL_KEYDOWN = bármilyen billentyű lenyomása
                if (!inCombat){
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        if (probapalya[MainPlayer.GetYPos() - 1][MainPlayer.GetXPos()] == 1) {
                            std::cout << "falnak utkoztem, a fal koordinatai:";
                            std::cout << MainPlayer.GetXPos() << " " << MainPlayer.GetYPos()-1 << std::endl;
                            break;
                        } else {
                            MainPlayer.SetYPos(MainPlayer.GetYPos()-1);
                            std::cout << "leptem, a jelenlegi koordinataim: " << MainPlayer.GetXPos() << " " << MainPlayer.GetYPos() << std::endl;
                            break;
                        }

                    case SDLK_DOWN:
                        if (probapalya[MainPlayer.GetYPos() + 1][MainPlayer.GetXPos()] == 1) {
                            std::cout << "falnak utkoztem, a fal koordinatai:";
                            std::cout << MainPlayer.GetXPos() << " " << MainPlayer.GetYPos()+1 << std::endl;
                            break;
                        } else {
                            MainPlayer.SetYPos(MainPlayer.GetYPos()+1);
                            std::cout << "leptem, a jelenlegi koordinataim: " << MainPlayer.GetXPos() << " " << MainPlayer.GetYPos() << std::endl;
                            break;
                        }

                    case SDLK_RIGHT:
                        if (probapalya[MainPlayer.GetYPos()][MainPlayer.GetXPos() + 1] == 1) {
                            std::cout << "falnak utkoztem, a fal koordinatai:";
                            std::cout << MainPlayer.GetXPos()+1 << " " << MainPlayer.GetYPos() << std::endl;
                            break;
                        } else {
                            MainPlayer.SetXPos(MainPlayer.GetXPos()+1);
                            std::cout << "leptem, a jelenlegi koordinataim: " << MainPlayer.GetXPos() << " " << MainPlayer.GetYPos() << std::endl;
                            break;
                        }

                    case SDLK_LEFT:
                        if (probapalya[MainPlayer.GetYPos()][MainPlayer.GetXPos() - 1] == 1) {
                            std::cout << "falnak utkoztem, a fal koordinatai:";
                            std::cout << MainPlayer.GetXPos()-1 << " " << MainPlayer.GetYPos() << std::endl;
                            break;
                        } else {
                            MainPlayer.SetXPos(MainPlayer.GetXPos()-1);
                            std::cout << "leptem, a jelenlegi koordinataim: " << MainPlayer.GetXPos() << " " << MainPlayer.GetYPos() << std::endl;
                            break;
                        }

                    default:
                        continue;
                }// switch
                }
                if (inCombat){
                switch (event.key.keysym.sym){
                    case SDLK_RETURN:
                        std::cout << "combatban vagyok, entert nyomtam" << std::endl;
                        break;
                    case SDLK_0:
                        std::cout << "kilepek a combatbol, megoltem az ellenseget" << std::endl;
                        auto it = std::find_if(EnemyList.begin(), EnemyList.end(), [target = MainPlayer.GetTarget()](Enemy* enemy) {
                            return enemy == target;  
                        });
                        if (it != EnemyList.end()) {
                            EnemyList.erase(it);
                            MainPlayer.SetTarget(nullptr);
                        } else {
                            std::cout << "nem talaltam meg a torlendo vector tagot" << std::endl;
                        }
                        inCombat = false;
                        break;
                }
                }
            }// if (event.type...
        }// while (poll event...

        //az adott színt az adott rendererre fogja váltani
        SDL_SetRenderDrawColor(renderer, 40, 80, 100, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);



        for (int x = 0; x < 15; x++) {
            for (int y = 0; y < 15; y++) {
                switch (probapalya[y][x]) {
                    case 1:
                        SDL_RenderCopy(renderer,
                                       texture1,
                                       NULL,
                                       &rectmap[x + (ScreenOffsetX/TEXTURE_W) - MainPlayer.GetXPos()][y + (ScreenOffsetY/TEXTURE_H) - MainPlayer.GetYPos()]
                                       );
                        break;

                    case 2:
                        SDL_RenderCopy(renderer,
                                       texture2,
                                       NULL,
                                       &rectmap[x + (ScreenOffsetX/TEXTURE_W) - MainPlayer.GetXPos()][y + (ScreenOffsetY/TEXTURE_H) - MainPlayer.GetYPos()]
                                       );
                        break;

                    case 0:
                        SDL_RenderCopy(renderer,
                                       texture0,
                                       NULL,
                                       &rectmap[x + (ScreenOffsetX/TEXTURE_W) - MainPlayer.GetXPos()][y + (ScreenOffsetY/TEXTURE_H) - MainPlayer.GetYPos()]
                                       );
                        break;

                    default:
                        continue;
                }// switch
            }//for (y...
        }// for (x...

                                                        //vegug nezzuk az enemylistet,
        auto it = EnemyList.begin();                    //de nem rendereljuk az enemyket az if miatt,
        while (it != EnemyList.end()){                  //kulon funkcioba at kell rakni kesobb
            (*it)->UpdateEntityPos(MainPlayer.GetXPos(),MainPlayer.GetYPos());  //a renderelest, vagy metoduskent atirni
            (*it)->RenderEntity(renderer);
            if(!inCombat && (
                ((*it)->GetXPos() == MainPlayer.GetXPos() && std::abs((*it)->GetYPos()-MainPlayer.GetYPos())==1) || 
                ((*it)->GetYPos() == MainPlayer.GetYPos() && std::abs((*it)->GetXPos()-MainPlayer.GetXPos())==1)
                )){
                std::cout << "egy enemy melle leptem" << std::endl;
                inCombat = 1;
                MainPlayer.SetTarget(*it);
                break;
            } else {
                ++it;
            }
        }

        auto it2 = EntityList.begin();    //egyelőre automatikusan felvesszük
        while (it2 != EntityList.end()){  //az entityket entitylistből, ha rajuk lepunk
            (*it2)->UpdateEntityPos(MainPlayer.GetXPos(),MainPlayer.GetYPos());
            (*it2)->RenderEntity(renderer);

            if((*it2)->GetXPos() == MainPlayer.GetXPos() && (*it2)->GetYPos() == MainPlayer.GetYPos()){
                it2 = EntityList.erase(it2);
                std::cout << "raleptem egy entity-re" << std::endl;
            } else {
                ++it2;
            }
        }

        MainPlayer.RenderEntity(renderer); // karakter helyzete
        SDL_RenderCopy(renderer, texture3, NULL, &character); 
        SDL_RenderPresent(renderer);            // jelenlegi render kirajzolás
    }// while (gameIsRunning)
    

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

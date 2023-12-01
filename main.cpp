//#define SDL_MAIN_HANDLED ezt ki kell kommentelni windows-on, attól függően, hogy mivel compile-olsz
#include <iostream>
#include <entity.hpp>
#include <enemy.hpp>
#include <player.hpp>
#include <inventory.hpp>
#include <text.hpp>
#include <vector>
#include <cmath>
#include <algorithm>

// from SDL
#include <SDL.h>
#include <SDL_ttf.h>

const int SCREEN_W = 640;
const int SCREEN_H = 512;
const int TEXTURE_W = 32;
const int TEXTURE_H = 32;
const int ScreenOffsetX = SCREEN_W / 2;
const int ScreenOffsetY = SCREEN_H / 2;

//ez az inventory slotok helyét keresi
//2 sor, 6 oszlop, minden egyes mező lényegében 32x32
//de a mezők között van egy kis elválasztó vonal is
//így 34-el osztok, hogy beleszámítsam azt
int InventorySlotNumber(int x, int y) {
    int rowNumber;
    int colNumber = std::floor(x/34)+1;
    if (y<=512 && y>=477) {
        rowNumber = 1;
    } else if (y<=476 && y>=442) {
        rowNumber = 0;
    } else {
        rowNumber = -1;
    }
    if ((rowNumber >= 0 && rowNumber <= 1) && (colNumber >=1 && colNumber<=6)){
        std::cout << (colNumber+rowNumber*6) << std::endl;
        return (colNumber+rowNumber*6);
    } else {
        std::cout << "a sor es oszlop szama: " << rowNumber << ", " << colNumber << std::endl;
        std::cout << "nem esett bele az inventory slotba" << std::endl;
        return 0;
    }
}

int showPrompt(SDL_Renderer* renderer, const std::string& question, std::string fontfilepath, int fontsize) {
    SDL_Event promptEvent;
    Text *yesText = new Text(fontfilepath, fontsize);
    Text *noText = new Text(fontfilepath, fontsize);
    Text *questionText = new Text(fontfilepath, fontsize);
    bool promptRunning = true;
    while (promptRunning) {
        while (SDL_PollEvent(&promptEvent)) {
            if (promptEvent.type == SDL_QUIT) {
                promptRunning = false;
            }
            else if (promptEvent.type == SDL_MOUSEBUTTONDOWN) {
                int mouseXPos, mouseYPos;
                SDL_GetMouseState(&mouseXPos, &mouseYPos);

                // Check if the mouse is over the yes button
                if (mouseXPos >= 100 && mouseXPos <= 200 && mouseYPos >= 300 && mouseYPos <= 350) {
                    delete yesText;
                    delete noText;
                    delete questionText;
                    return 1; // Yes button pressed
                }

                // Check if the mouse is over the no button
                if (mouseXPos >= 300 && mouseXPos <= 400 && mouseYPos >= 300 && mouseYPos <= 350) {
                    delete yesText;
                    delete noText;
                    delete questionText;
                    return 0; // No button pressed
                }
            }
        }

        SDL_RenderClear(renderer);
        questionText->DrawText(renderer, question, 50, 50, 500, 50);
        yesText->DrawText(renderer, "Igen", 100, 300, 100, 50);
        noText->DrawText(renderer, "Nem", 340, 300, 100, 50);
        SDL_RenderPresent(renderer);
    }

    delete yesText;
    delete noText;
    delete questionText;

    return -1; // Error or exit
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window* window=nullptr;
    SDL_Renderer* renderer=nullptr;

    window = SDL_CreateWindow("MOSZE test",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_W,
                              SCREEN_H,
                              SDL_WINDOW_SHOWN
                              );

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    Player MainPlayer(renderer,"./assets/black.bmp",4,4,10);
    Inventory MainInventory(renderer);

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

    SDL_Surface* surface0 = SDL_LoadBMP("./assets/purple.bmp");
    SDL_Texture* texture0 = SDL_CreateTextureFromSurface(renderer,surface0);

    SDL_Surface* surface1 = SDL_LoadBMP("./assets/red.bmp");
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer,surface1);

    SDL_Surface* surface2 = SDL_LoadBMP("./assets/green.bmp");
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer,surface2);

    unsigned int startTime = 0, endTime;
    bool gameIsRunning = true;
    SDL_Event event;
    bool inCombat = 0;
    bool inInventory = 0;
    bool toggleInventory = 0;

    while(gameIsRunning) {                       // event loop, PollEvent-el végig megyünk minden egyes event-en
        startTime = SDL_GetTicks();            //ezzel fogom cappelni a framerate-et, a játéknak nem kell végtelen fps, túl nagy igénye lenne
        int mouseXPos,mouseYPos;
        Uint32 mouseButtons;
        mouseButtons = SDL_GetMouseState(&mouseXPos,&mouseYPos);
        while(SDL_PollEvent(&event)) {           // ezekre különböző módon írunk "válaszokat"
            if(event.type == SDL_QUIT) {         // SDL_QUIT = sarokban lévő X-el bezárás
                gameIsRunning = false;
                break;
            }
            if(event.type == SDL_KEYDOWN) {     // SDL_KEYDOWN = bármilyen billentyű lenyomása
                if (!inCombat && !inInventory) {
                switch (event.key.keysym.sym) {
                    case SDLK_e: {
                            std::cout << "inInventory false, atvaltom true-ra" << std::endl;
                            toggleInventory = 1;
                            break;
                        }
                    case SDLK_t: {
                            int answer = showPrompt(renderer, "proba","./fonts/RPGSystem.ttf",16);
                    }
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
            if (inInventory) {
            if (event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_e) {
                    std::cout << "inInventory true, atvaltom false-ra" << std::endl;
                    toggleInventory = 1;
                    break;
                }
            } 
            if(event.button.button == SDL_BUTTON_LEFT){
                std::cout << "bal eger lenyomva" << std::endl;
                std::cout << "a koordinatai: " << mouseXPos << ", " << mouseYPos << std::endl;
                InventorySlotNumber(mouseXPos,mouseYPos);
            }
            }
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
        
        if (toggleInventory) {          //a legelejen atvaltjuk az inInventory-t true-ra E lenyomasara, es utana pedig
            if (inInventory) {          //megvizsgaljuk, hogy true-e, de mivel tul gyorsan fut a jatek
                inInventory = false;    //ezert mindkettonel aktivalodik az E lenyomas, igy kulon kell valtogatni a loop utan
            } else {
                inInventory = true;
            }
            toggleInventory = false;
        }
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

        if (inInventory) {MainInventory.RenderInventory(renderer);}
        MainPlayer.RenderEntity(renderer); // karakter helyzete
        SDL_RenderPresent(renderer);             // jelenlegi render kirajzolás
        endTime = SDL_GetTicks() - startTime;    // startTime és endTime közti különbség MS-ben
        if (endTime < 33) {                      // 33-ra nézzük, mivel 1s-et így 30-ra oszt a 33ms, azaz 30 fps-t kapunk
            SDL_Delay(33 - endTime);             // delayt rakunk be, ha netalán gyorsabban lefut egy loop, mint 33ms
        }
    }// while (gameIsRunning)

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

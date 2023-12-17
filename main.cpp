#define SDL_MAIN_HANDLED
#include "enemy.hpp"
#include "entity.hpp"
#include "inventory.hpp"
#include "maze.hpp"
#include "player.hpp"
#include "text.hpp"

// from stdlib
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

// from SDL2
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>


const int SCREEN_W = 672;
const int SCREEN_H = 672;
const int TEXTURE_W = 32;
const int TEXTURE_H = 32;
const int ScreenOffsetX = 0;
const int ScreenOffsetY = 0;


void RunGame(SDL_Renderer* renderer,
             std::vector<std::vector<int>> probapalya,
             Player MainPlayer,
             std::vector<Entity*> EntityList,
             std::vector<Enemy*> EnemyList,
             std::vector<Entity*> KeyList,
             SDL_Rect rectmap[40][40],
             Inventory MainInventory,
             SDL_Surface* surface1,
             SDL_Texture* texture1,
             SDL_Surface* surface2,
             SDL_Texture* texture2,
             SDL_Surface* surface3,
             SDL_Texture* texture3,
             bool gameBeaten,
             bool* hasDied
             );

void showScore(SDL_Renderer* renderer, const std::string& score, std::string fontfilepath, int fontsize);
void showLoseScreen(SDL_Renderer* renderer, std::string fontfilepath, int fontsize);

bool DoTheyCollide (int enemyYpos, int enemyXpos, int playerYpos, int playerXpos);

int showPrompt(SDL_Renderer* renderer, const std::string& question, std::string fontfilepath, int fontsize);

//ez az inventory slotok helyét keresi
//2 sor, 6 oszlop, minden egyes mező lényegében 32x32
//de a mezők között van egy kis elválasztó vonal is
//így 34-el osztok, hogy beleszámítsam azt
int InventorySlotNumber(int x, int y) {
    int rowNumber;
    int colNumber = std::floor(x / 34) + 1;
    if (y <= 512 && y >= 477) {
        rowNumber = 1;
    }
    else if (y <= 476 && y >= 442) {
        rowNumber = 0;
    }
    else {
        rowNumber = -1;
    }
    if ((rowNumber >= 0 && rowNumber <= 1) && (colNumber >= 1 && colNumber <= 6)) {
        std::cout << (colNumber + rowNumber * 6) << std::endl;
        return (colNumber + rowNumber * 6);
    }
    else {
        std::cout << "a sor es oszlop szama: " << rowNumber << ", " << colNumber << std::endl;
        std::cout << "nem esett bele az inventory slotba" << std::endl;
        return 0;
    }
}




int main(int argc, char* argv[])
{ // init
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    window = SDL_CreateWindow("MOSZE test",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              SCREEN_W,
                              SCREEN_H,
                              SDL_WINDOW_SHOWN
                              );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Inventory MainInventory(renderer);

    SDL_Surface* surface1 = SDL_LoadBMP("./assets/wall.bmp");
    SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
    SDL_Surface* surface2 = SDL_LoadBMP("./assets/Tiles.bmp");
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_Surface* surface3 = SDL_LoadBMP("./assets/wizard.bmp");
    SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer, surface3);

    auto score = std::chrono::seconds(0);
    bool gameBeaten = false;
    bool AllEntitiesCollected = true;
    bool hasDied = false;

    const int MAX_ROUNDS = 2;       //ez adja meg, hogy hány labirintuson kell végigmennünk, hogy kivigyük a játékot
    for (int rounds = 0; rounds < MAX_ROUNDS; rounds++) {
// játékos pozícióját visszateszi 1-re amikor új mapra ér
        Player MainPlayer(renderer, "./assets/wizard.bmp", 1, 1, 10);
        MainPlayer.SetXPos(1);
        MainPlayer.SetYPos(1);

// map generálása 
        std::vector<std::vector<int>> probapalya;

        Maze maze;
        maze.generateMaze();
        probapalya = maze.getMazeMatrix();

        SDL_Rect rectmap[40][40];
        for (int x = 0; x < 40; x++)
            for (int y = 0; y < 40; y++) {
                rectmap[x][y].x = x * 32;
                rectmap[x][y].y = y * 32;
                rectmap[x][y].w = 32;
                rectmap[x][y].h = 32;
            }


// kulcsok generálása
        std::vector<Entity*> KeyList;
        for (int key = 0; key < 3; key++)
        {
            int r1, r2;
            bool rosszhely = true;
            do {
                r1 = 2 + (rand() % 19);
                r2 = 2 + (rand() % 19);
                if (probapalya[r1][r2] == 2) {
                    rosszhely = false;
                }

            } while (rosszhely);
            KeyList.push_back(new Entity(renderer, "./assets/key.bmp", r2, r1));
        }


// potik generálása
        std::vector<Entity*> EntityList;
        for (int entity = 0; entity < 10; entity++)
        {
            int r1, r2;
            bool rosszhely = true;
            do {
                r1 = 2 + (rand() % 19);
                r2 = 2 + (rand() % 19);
                if (probapalya[r1][r2] == 2) {
                    rosszhely = false;
                }

                for (auto& key : KeyList) {
                    if (key->GetXPos() == r2 && key->GetYPos() == r1) {
                        rosszhely = true;
                        break;
                    }
                }
            } while (rosszhely);
            EntityList.push_back(new Entity(renderer, "./assets/potion.bmp", r2, r1));
        }

        
// ellenfelek generálása
        std::vector<Enemy*> EnemyList;
        for (int enemy = 0; enemy < 10; enemy++)
        {
            int r1, r2;
            bool rosszhely = true;
            do {
                r1 = 2 + (rand() % 19);
                r2 = 2 + (rand() % 19);
                if (probapalya[r1][r2] == 2) {
                    rosszhely = false;
                }
            } while (rosszhely);
            EnemyList.push_back(new Enemy(renderer, "./assets/skeleton.bmp", r2, r1, 3, "orc"));
        }


// játék lefutása
        std::chrono::steady_clock::time_point mapStarted = std::chrono::steady_clock::now();

        if (!hasDied) 
            RunGame(renderer,
                    probapalya,
                    MainPlayer,
                    EntityList,
                    EnemyList,
                    KeyList,
                    rectmap,
                    MainInventory,
                    surface1,
                    texture1,
                    surface2,
                    texture2,
                    surface3,
                    texture3,
                    gameBeaten,
                    &hasDied
                    );

        std::chrono::steady_clock::time_point mapEnded = std::chrono::steady_clock::now();

        if (hasDied) {
            showLoseScreen(renderer, "./fonts/RPGSystem.ttf", 16);
            break;
        }

        for (auto& entity : EntityList)
            AllEntitiesCollected = false;

        score = score + std::chrono::duration_cast<std::chrono::seconds>(mapEnded - mapStarted);
    }

    if (hasDied) {
        showLoseScreen(renderer, "./fonts/RPGSystem.ttf", 16);
    } else {
        int scoreAsInt = score.count ();
        scoreAsInt = 10000 / scoreAsInt;        //pontszámszámláló
        showScore(renderer, std::to_string(scoreAsInt), "./fonts/RPGSystem.ttf", 16);  //megmutatja a pontszámod ha meghaltál
    
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


void RunGame(SDL_Renderer* renderer,
             std::vector<std::vector<int>> probapalya,
             Player MainPlayer,
             std::vector<Entity*> EntityList,
             std::vector<Enemy*> EnemyList,
             std::vector<Entity*> KeyList,
             SDL_Rect rectmap[40][40],
             Inventory MainInventory,
             SDL_Surface* surface1,
             SDL_Texture* texture1,
             SDL_Surface* surface2,
             SDL_Texture* texture2,
             SDL_Surface* surface3,
             SDL_Texture* texture3,
             bool gameBeaten,
             bool* hasDied
             ){
    bool gameIsRunning = true;
    SDL_Event event;
    bool inCombat = false;
    bool inInventory = false;
    bool toggleInventory = false;
    unsigned int startTime = 0, endTime;
    int keysGot = 0;

    while (gameIsRunning) {                       // event loop, PollEvent-el végig megyünk minden egyes event-en

        startTime = SDL_GetTicks();            //ezzel fogom cappelni a framerate-et, a játéknak nem kell végtelen fps, túl nagy igénye lenne
        int mouseXPos, mouseYPos;
        Uint32 mouseButtons;
        mouseButtons = SDL_GetMouseState(&mouseXPos, &mouseYPos);

        while (SDL_PollEvent(&event)) {           // ezekre különböző módon írunk "válaszokat"
            if (event.type == SDL_QUIT) {         // SDL_QUIT = sarokban lévő X-el bezárás
                gameIsRunning = false;
                break;
            }
            if (event.type == SDL_KEYDOWN) {     // SDL_KEYDOWN = bármilyen billentyű lenyomása

                for (auto& enemy : EnemyList)
                    enemy->Patrol(probapalya);      

                if (!inCombat && !inInventory) {
                    switch (event.key.keysym.sym) {
                        case SDLK_e: {
                            std::cout << "inInventory false, atvaltom true-ra" << std::endl;
                            toggleInventory = true;
                            break;
                        }
                        case SDLK_t: {
                            int answer = showPrompt(renderer, "proba", "./fonts/RPGSystem.ttf", 16);
                        }
                        case SDLK_UP:
                            if (probapalya[MainPlayer.GetYPos() - 1][MainPlayer.GetXPos()] == 1) {
                                std::cout << "falnak utkoztem, a fal koordinatai:";
                                std::cout << MainPlayer.GetXPos() << " " << MainPlayer.GetYPos() - 1 << std::endl;
                                break;
                            }
                            else {
                                MainPlayer.SetYPos(MainPlayer.GetYPos() - 1);
                                std::cout << "leptem, a jelenlegi koordinataim: " << MainPlayer.GetXPos() << " " << MainPlayer.GetYPos() << std::endl;
                                break;
                            }

                        case SDLK_DOWN:
                            if (probapalya[MainPlayer.GetYPos() + 1][MainPlayer.GetXPos()] == 1) {
                                std::cout << "falnak utkoztem, a fal koordinatai:";
                                std::cout << MainPlayer.GetXPos() << " " << MainPlayer.GetYPos() + 1 << std::endl;
                                break;
                            }
                            else {
                                MainPlayer.SetYPos(MainPlayer.GetYPos() + 1);
                                std::cout << "leptem, a jelenlegi koordinataim: " << MainPlayer.GetXPos() << " " << MainPlayer.GetYPos() << std::endl;
                                break;
                            }

                        case SDLK_RIGHT:
                            if (probapalya[MainPlayer.GetYPos()][MainPlayer.GetXPos() + 1] == 1) {

                                std::cout << "falnak utkoztem, a fal koordinatai:";
                                std::cout << MainPlayer.GetXPos() + 1 << " " << MainPlayer.GetYPos() << std::endl;
                                break;
                            }
                            else {
                                MainPlayer.SetXPos(MainPlayer.GetXPos() + 1);
                                std::cout << "leptem, a jelenlegi koordinataim: " << MainPlayer.GetXPos() << " " << MainPlayer.GetYPos() << std::endl;
                                break;
                            }

                        case SDLK_LEFT:
                            if (probapalya[MainPlayer.GetYPos()][MainPlayer.GetXPos() - 1] == 1) {
                                std::cout << "falnak utkoztem, a fal koordinatai:";
                                std::cout << MainPlayer.GetXPos() - 1 << " " << MainPlayer.GetYPos() << std::endl;
                                break;
                            }
                            else {
                                MainPlayer.SetXPos(MainPlayer.GetXPos() - 1);
                                std::cout << "leptem, a jelenlegi koordinataim: " << MainPlayer.GetXPos() << " " << MainPlayer.GetYPos() << std::endl;
                                break;
                            }

                        default:
                            continue;
                    }// switch
                }
            }// if (event.type...
            if (inInventory) {
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_e) {
                        std::cout << "inInventory true, atvaltom false-ra" << std::endl;
                        toggleInventory = true;
                        break;
                    }
                }
                if (event.button.button == SDL_BUTTON_LEFT) {
                    std::cout << "bal eger lenyomva" << std::endl;
                    std::cout << "a koordinatai: " << mouseXPos << ", " << mouseYPos << std::endl;
                    InventorySlotNumber(mouseXPos, mouseYPos);
                }
            }
        }// while (poll event...

        //az adott színt az adott rendererre fogja váltani
        SDL_SetRenderDrawColor(renderer, 40, 80, 100, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for (int x = 0; x < 21; x++) {
            for (int y = 0; y < 21; y++) {
                switch (probapalya[y][x]) {
                    case 1:
                        SDL_RenderCopy(renderer,
                                       texture1,
                                       NULL,
                                       &rectmap[x + (ScreenOffsetX / TEXTURE_W)][y + (ScreenOffsetY / TEXTURE_H)]
                                       );
                        break;

                    case 2:
                        SDL_RenderCopy(renderer,
                                       texture2,
                                       NULL,
                                       &rectmap[x + (ScreenOffsetX / TEXTURE_W)][y + (ScreenOffsetY / TEXTURE_H)]
                                       );
                        break;

                    case 0:
                        SDL_RenderCopy(renderer,
                                       texture3,
                                       NULL,
                                       &rectmap[x + (ScreenOffsetX / TEXTURE_W)][y + (ScreenOffsetY / TEXTURE_H)]
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
            }
            else {
                inInventory = true;
            }
            toggleInventory = false;
        }


        //végig nézzük az enemy list-et
        auto it = EnemyList.begin();                   ,
        while (it != EnemyList.end()) {                  
            (*it)->UpdateEntityPos(MainPlayer.GetXPos(), MainPlayer.GetYPos());  
            (*it)->RenderEntity(renderer);
            if (!inCombat && DoTheyCollide((*it)->GetYPos(), (*it)->GetXPos(), MainPlayer.GetYPos(), MainPlayer.GetXPos())) {

                    MainPlayer.SetHealth (MainPlayer.GetHealth () - 3);     //ennyi életerőt von le, ha megütközöl egy ellenféllel
                    inCombat = true;
                    MainPlayer.SetTarget(*it);
                    std::cout << "CurrentHP = " << MainPlayer.GetHealth () << std::endl;
                    std::cout << "kilepek a combatbol, megoltem az ellenseget" << std::endl;
                    auto it = std::find_if(EnemyList.begin(), EnemyList.end(), [target = MainPlayer.GetTarget()](Enemy* enemy) {
                        return enemy == target;
                    });


                    if (it != EnemyList.end()) {
                        EnemyList.erase(it);
                        MainPlayer.SetTarget(nullptr);
                    }
                    else {
                        std::cout << "nem talaltam meg a torlendo vector tagot" << std::endl;
                    }
                    inCombat = false;
                    break;
            }
            else {
                ++it;
            }
        }


        auto it2 = EntityList.begin();    //automatikusan felvesszük az potikat entitylistből, ha rájuk lepunk
        while (it2 != EntityList.end()) {  
            (*it2)->UpdateEntityPos(MainPlayer.GetXPos(), MainPlayer.GetYPos());
            (*it2)->RenderEntity(renderer);
            if ((*it2)->GetXPos() == MainPlayer.GetXPos() && (*it2)->GetYPos() == MainPlayer.GetYPos()) {
                it2 = EntityList.erase(it2);
                MainPlayer.SetHealth(10);
                std::cout << "NewHP = " << MainPlayer.GetHealth() << std::endl;
            }
            else {
                ++it2;
            }
        }


        auto it3 = KeyList.begin();    //automatikusan felvesszük az kulcsokat keylistből, ha rájuk lepunk
        while (it3 != KeyList.end()) {  
            (*it3)->UpdateEntityPos(MainPlayer.GetXPos(), MainPlayer.GetYPos());
            (*it3)->RenderEntity(renderer);
            if ((*it3)->GetXPos() == MainPlayer.GetXPos() && (*it3)->GetYPos() == MainPlayer.GetYPos()) {
                it3 = KeyList.erase(it3);
                keysGot++;
            }
            else {
                ++it3;
            }
        }


        for (auto& entity : EntityList) {
            entity->UpdateEntityPos (entity->GetXPos (), entity->GetYPos ());
            entity->RenderEntity (renderer);
        }


        if (inInventory) 
            MainInventory.RenderInventory(renderer);

        MainPlayer.UpdateEntityPos (MainPlayer.GetXPos (),MainPlayer.GetYPos ());
        MainPlayer.RenderEntity (renderer); // karakter helyzete
        SDL_RenderPresent(renderer);             // jelenlegi render kirajzolás
        endTime = SDL_GetTicks() - startTime;    // startTime és endTime közti különbség MS-ben
        if (endTime < 33) {                      // 33-ra nézzük, mivel 1s-et így 30-ra oszt a 33ms, azaz 30 fps-t kapunk
            SDL_Delay(33 - endTime);             // delayt rakunk be, ha netalán gyorsabban lefut egy loop, mint 33ms
        }


        if (MainPlayer.GetHealth() <= 0) {
            gameIsRunning = false;
            *hasDied = true;
        }

        if ((keysGot == 3 && MainPlayer.GetXPos() == 19) && (MainPlayer.GetYPos() == 19)) {     // ha megvan mind3 kulcsod és a megfelelő helyen vagy, továbbmehetsz a következő pályára
            gameIsRunning = false;
            gameBeaten = true;
        }
    }// while (gameIsRunning)
}


int showPrompt(SDL_Renderer* renderer, const std::string& question, std::string fontfilepath, int fontsize) {
    SDL_Event promptEvent;
    Text* yesText = new Text(fontfilepath, fontsize);
    Text* noText = new Text(fontfilepath, fontsize);
    Text* questionText = new Text(fontfilepath, fontsize);
    bool promptRunning = true;
    while (promptRunning) {
        while (SDL_PollEvent(&promptEvent)) {
            if (promptEvent.type == SDL_QUIT) {
                promptRunning = false;
            }
            else if (promptEvent.type == SDL_MOUSEBUTTONDOWN) {
                int mouseXPos, mouseYPos;
                SDL_GetMouseState(&mouseXPos, &mouseYPos);
                if (mouseXPos >= 100 && mouseXPos <= 200 && mouseYPos >= 300 && mouseYPos <= 350) {
                    delete yesText;
                    delete noText;
                    delete questionText;
                    return 1;
                }

                if (mouseXPos >= 300 && mouseXPos <= 400 && mouseYPos >= 300 && mouseYPos <= 350) {
                    delete yesText;
                    delete noText;
                    delete questionText;
                    return 0;
                }
            }
        }

        SDL_RenderClear(renderer);
        questionText->DrawText(renderer, question, 50, 50, 300, 150);
        SDL_RenderPresent(renderer);
    }

    delete yesText;
    delete noText;
    delete questionText;

    return -1; // Error or exit
}


void showScore(SDL_Renderer* renderer, const std::string& score, std::string fontfilepath, int fontsize) {
    std::string scoreFinal = "Score: " + score;
    SDL_Event promptEvent;
    Text* continueText = new Text(fontfilepath, fontsize);
    Text* scoreText = new Text(fontfilepath, fontsize);
    bool promptRunning = true;
    while (promptRunning) {
        while (SDL_PollEvent(&promptEvent)) {
            if (promptEvent.type == SDL_QUIT)
                promptRunning = false;
            if (promptEvent.type == SDL_MOUSEBUTTONDOWN) 
                promptRunning = false;

            SDL_RenderClear(renderer);
            scoreText->DrawText(renderer, scoreFinal, 50, 50, 300, 100);
            continueText->DrawText(renderer, "Click anywhere to quit.", 100, 300, 370, 70);
            SDL_RenderPresent(renderer);
        }
    }
    delete scoreText;
    return; // Error or exit
}


void showLoseScreen(SDL_Renderer* renderer, std::string fontfilepath, int fontsize) {
    std::string scoreFinal = "Lose";
    SDL_Event promptEvent;
    Text* continueText = new Text(fontfilepath, fontsize);
    Text* scoreText = new Text(fontfilepath, fontsize);
    bool promptRunning = true;
    while (promptRunning) {
        while (SDL_PollEvent(&promptEvent)) {
            if (promptEvent.type == SDL_QUIT)
                promptRunning = false;
            if (promptEvent.type == SDL_MOUSEBUTTONDOWN) 
                promptRunning = false;

            SDL_RenderClear(renderer);
            scoreText->DrawText(renderer, scoreFinal, 50, 50, 300, 100);
            continueText->DrawText(renderer, "Click anywhere to quit.", 100, 300, 370, 70);
            SDL_RenderPresent(renderer);
        }
    }
    delete scoreText;
    return; // Error or exit
}


bool DoTheyCollide (int enemyYpos, int enemyXpos, int playerYpos, int playerXpos) {     //megnézi, hogy egy mezős körzetünkben van e enemy
    if (enemyXpos == playerXpos)
        if (enemyYpos == playerYpos)
            return true;

    if (enemyXpos - 1 == playerXpos)
        if (enemyYpos == playerYpos)
            return true;

    if (enemyXpos + 1 == playerXpos)
        if (enemyYpos == playerYpos)
            return true;

    if (enemyXpos == playerXpos)
        if (enemyYpos - 1 == playerYpos)
            return true;

    if (enemyXpos == playerXpos)
        if (enemyYpos + 1 == playerYpos)
            return true;

    return false;
}
        

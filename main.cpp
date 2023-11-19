#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

// from SDL
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_surface.h>


const int SCREEN_W = 640;
const int SCREEN_H = 512;
const int TEXTURE_W = 32;
const int TEXTURE_H = 32;


std::filesystem::path* GetNewSaveFile (std::filesystem::path *savePath)
{
    savePath->make_preferred();  // \ <-> / OS-szerint preferáltra cseréli
    int fileNo = 0;
    bool fileExists = true;

    do {
        savePath->replace_filename("save_" + std::to_string(fileNo));
        savePath->replace_extension(".bin");

        fileExists = std::filesystem::exists(*savePath);
        fileNo++;
    } while (fileExists);

    return savePath;
}


void SaveMapToFile (std::vector<std::vector<int>> &vMap, std::filesystem::path savePath)
{
    std::ofstream saveFile (GetNewSaveFile (&savePath)->c_str ());

    for (auto row : vMap) {
        for (auto value : row) {
            saveFile << value;
        }
        saveFile << std::endl;
    }
    saveFile.close();
}


std::vector<std::vector<int>> OpenSave (std::filesystem::path savePath)
{
    std::ifstream saveFile (savePath);
    std::string line;

    std::vector<int> tmpVec;
    std::vector<std::vector<int>> returnMatrix;

    while (std::getline (saveFile, line)) {
        tmpVec.clear ();
        for (auto value : line) {
            tmpVec.push_back (int (value - '0'));         // <---- Ömm igen... valami szebb megoldás?!
        }
        returnMatrix.push_back (tmpVec);
    }
    return returnMatrix;
}


int main(int argc, char* argv[])
{
    int ScreenOffsetX = SCREEN_W / 2;
    int ScreenOffsetY = SCREEN_H / 2;

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

    std::vector<std::vector<int>> probapalya =
    {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,1,1,1,0,0,0},
        {0,0,0,1,2,2,1,0,0,0},
        {0,1,1,1,2,2,1,1,1,0},
        {0,1,2,2,2,2,2,2,1,0},
        {0,1,2,2,1,1,2,2,1,0},
        {0,1,1,2,2,2,2,1,1,0},
        {0,0,1,2,2,2,2,1,0,0},
        {0,0,1,1,1,1,1,1,0,0},
        {1,0,0,0,0,0,0,0,0,2}
    };

    SDL_Rect rectmap[40][40];
    for (int x=0; x < 40; x++)
        for (int y=0; y < 40; y++) {
            rectmap[x][y].x = x*32;
            rectmap[x][y].y = y*32;
            rectmap[x][y].w = 32;
            rectmap[x][y].h = 32;
        }
    

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

                    case SDLK_q:
                        gameIsRunning = false;
                        break;

                    default:
                        continue;
                }// switch
            }// if (event.type...
        }// while (poll event...

        //az adott színt az adott rendererre fogja váltani
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for (int x = 0; x < probapalya.size (); x++) {
            for (int y = 0; y < probapalya[x].size (); y++) {
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
        
        SDL_RenderCopy(renderer, texture3, NULL, &character); // karakter helyzete
        SDL_RenderPresent(renderer);            // jelenlegi render kirajzolás
    }// while (gameIsRunning)
    

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

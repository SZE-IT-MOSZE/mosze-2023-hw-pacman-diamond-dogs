#define SDL_MAIN_HANDLED
#include <iostream>

// from SDL
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_surface.h>


const int SCREEN_W = 640;
const int SCREEN_H = 512;
const int TEXTURE_W = 32;
const int TEXTURE_H = 32;
const int ScreenOffsetX = SCREEN_W / 2;
const int ScreenOffsetY = SCREEN_H / 2;

class Entity {
    private:
    SDL_Texture* entityTexture;
    SDL_Rect entityRect;
    int xPos;
    int yPos;
    
    public:
    Entity(SDL_Renderer*& renderer, std::string path, int x, int y) {
        xPos = x;
        yPos = y;
        entityRect.x = x*32 + ScreenOffsetX/TEXTURE_W;
        entityRect.y = y*32 + ScreenOffsetY/TEXTURE_H;
        entityRect.w = TEXTURE_W;
        entityRect.h = TEXTURE_H;
        SDL_Surface* surface = SDL_LoadBMP(path.c_str());
        entityTexture = SDL_CreateTextureFromSurface(renderer, surface);
    }
    ~Entity();
    void RenderEntity(SDL_Renderer*& renderer){
        SDL_RenderCopy(renderer, entityTexture, NULL, &entityRect);
    }
    void MoveEntity(int x, int y){
        xPos = x;
        yPos = y;
    }
    void UpdateEntityPos(int charXPos, int charYPos){
        entityRect.x = (xPos + (ScreenOffsetX/TEXTURE_W) - charXPos)*32;
        entityRect.y = (yPos + (ScreenOffsetY/TEXTURE_H) - charYPos)*32;
    }
};

int main(int argc, char* argv[])
{


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

    int probapalya[10][10] =
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
    
    Entity *testentity = new Entity(renderer,"./assets/blue.bmp",3,3);    //proba az uj classra

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

        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
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

        testentity->UpdateEntityPos(charXPos,charYPos);  //először update-eljük a player helyzetével
        testentity->RenderEntity(renderer);              //és csak ezután rendereljük, a tile-ok után
        
        SDL_RenderCopy(renderer, texture3, NULL, &character); // karakter helyzete
        SDL_RenderPresent(renderer);            // jelenlegi render kirajzolás
    }// while (gameIsRunning)
    

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

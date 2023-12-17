#ifndef ENTITY_HPP      //entity fájlok header-e
#define ENTITY_HPP

// from SDL2
#include <SDL2/SDL.h>


// from stdlib
#include <string>


class Entity {              //életerõ potik és kulcsok
private:
    SDL_Texture* entityTexture;
    SDL_Rect entityRect;
    int xPos;
    int yPos;
    
public:
    Entity(SDL_Renderer* renderer, std::string path, int x, int y);
    ~Entity();
    void RenderEntity(SDL_Renderer* renderer);
    void MoveEntity(int x, int y);
    void SetRectPos(int rectx, int recty);
    void UpdateEntityPos(int charXPos, int charYPos);
    int GetXPos();
    int GetYPos();
    void SetXPos(int x);
    void SetYPos(int y);
};

#endif //ENTITY_HPP

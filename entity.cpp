#include "entity.hpp"


Entity::Entity(SDL_Renderer* renderer, std::string path, int x, int y) {
    xPos = x;
    yPos = y;
    entityRect.x = x*32;
    entityRect.y = y*32;
    entityRect.w = 32;
    entityRect.h = 32;
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    entityTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Entity::~Entity(){
    SDL_DestroyTexture(entityTexture);
};

void Entity::RenderEntity(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, entityTexture, NULL, &entityRect);
};

void Entity::MoveEntity(int x, int y){
    xPos = x;
    yPos = y;
    UpdateEntityPos(x, y);
};

void Entity::SetRectPos(int rectx, int recty){
    entityRect.x = rectx;
    entityRect.y = recty;
}

void Entity::UpdateEntityPos(int charXPos, int charYPos){
    entityRect.x = xPos * 32;
    entityRect.y = yPos * 32;
};

int Entity::GetXPos(){
    return xPos;
};

int Entity::GetYPos(){
    return yPos;
};

void Entity::SetXPos(int x){
    xPos = x;
};

void Entity::SetYPos(int y){
   yPos = y;
};

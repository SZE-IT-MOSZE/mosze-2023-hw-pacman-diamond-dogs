#include <entity.hpp>
#include <iostream>
const int SCREEN_W = 640;
const int SCREEN_H = 512;
const int TEXTURE_W = 32;
const int TEXTURE_H = 32;
const int ScreenOffsetX = SCREEN_W / 2;
const int ScreenOffsetY = SCREEN_H / 2;

Entity::Entity(SDL_Renderer*& renderer, std::string path, int x, int y) {
    xPos = x;
    yPos = y;
    entityRect.x = x*32 + ScreenOffsetX/TEXTURE_W;
    entityRect.y = y*32 + ScreenOffsetY/TEXTURE_H;
    entityRect.w = TEXTURE_W;
    entityRect.h = TEXTURE_H;
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    entityTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Entity::~Entity(){
    SDL_DestroyTexture(entityTexture);
};

void Entity::RenderEntity(SDL_Renderer*& renderer){
    SDL_RenderCopy(renderer, entityTexture, NULL, &entityRect);
};

void Entity::MoveEntity(int x, int y){
    xPos = x;
    yPos = y;
};

void Entity::UpdateEntityPos(int charXPos, int charYPos){
    entityRect.x = (xPos + (ScreenOffsetX/TEXTURE_W) - charXPos)*32;
    entityRect.y = (yPos + (ScreenOffsetY/TEXTURE_H) - charYPos)*32;
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
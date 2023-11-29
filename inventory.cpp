#include <inventory.hpp>
#include <iostream>
const int SCREEN_W = 640;
const int SCREEN_H = 512;
const int TEXTURE_W = 32;
const int TEXTURE_H = 32;
const int ScreenOffsetX = SCREEN_W / 2;
const int ScreenOffsetY = SCREEN_H / 2;

Inventory::Inventory(SDL_Renderer* renderer){
    InventoryItems.reserve(12);
    backgroundRect.x = 0;
    backgroundRect.y = 442;
    backgroundRect.w = 206;
    backgroundRect.h = 70;
    SDL_Surface* surface = SDL_LoadBMP("./assets/black.bmp");
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Inventory::~Inventory() {
    for (Entity* item : InventoryItems) {
        delete item;
    }
    InventoryItems.clear();
}

bool Inventory::AddItem(Entity* item) {
    if (InventoryItems.size() < capacity) {
        InventoryItems.push_back(item);
        return true;
    } else {
        return false;
    }
}

void Inventory::RenderInventory(SDL_Renderer* &renderer){
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect);
}
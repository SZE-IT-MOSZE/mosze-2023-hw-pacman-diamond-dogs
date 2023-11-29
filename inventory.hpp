#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <SDL.h>
#include <entity.hpp>

class Inventory {
    private:
    SDL_Texture* backgroundTexture;
    SDL_Rect backgroundRect;
    std::vector<Entity*> InventoryItems;
    size_t capacity = 8;

    public:
    Inventory(SDL_Renderer* renderer);
    ~Inventory();
    bool AddItem(Entity* item);
    void RenderInventory(SDL_Renderer* renderer);
};

#endif //INVENTORY_HPP
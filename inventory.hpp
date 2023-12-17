#ifndef INVENTORY_HPP   //inventory header, végül nem volt idõnk ezzel foglalkozni :(
#define INVENTORY_HPP


#include "entity.hpp"

// from stdlib
#include <vector>

// from SDL2
#include <SDL2/SDL.h>


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
    void RenderInventory(SDL_Renderer* &renderer);
};

#endif //INVENTORY_HPP

#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <entity.hpp>

class Inventory {
    private:
    std::vector<Entity*> InventoryItems;
    size_t capacity = 8;

    public:
    Inventory() = default;
    ~Inventory();
    bool AddItem(Entity* item);
};

#endif //INVENTORY_HPP
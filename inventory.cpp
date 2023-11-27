#include <inventory.hpp>
#include <iostream>

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
#ifndef ENEMY_HPP       //ellenfelek header fájla
#define ENEMY_HPP

#include "entity.hpp"
#include "direction.hpp"

#include <cstdlib>
#include <vector>
#include <iostream>


class Enemy : public Entity {

private:
    int health;
    std::string name;
    Direction heading;

    bool NextTileIsFree (int tile);

public:
    Enemy (SDL_Renderer*& renderer, std::string path, int x, int y, int initHealth, std::string monsterName);
    int GetHealth ();
    void SetHealth (int newHealth);
    void Patrol (std::vector<std::vector<int>> map);
};

#endif //ENEMY_HPP

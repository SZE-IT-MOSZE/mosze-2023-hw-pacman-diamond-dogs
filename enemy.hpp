#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <entity.hpp>

class Enemy : public Entity {
    private:
    int health;
    std::string name;

    public:
    Enemy(SDL_Renderer*& renderer, std::string path, int x, int y, int initHealth, std::string monsterName);
    int GetHealth();
    void SetHealth(int newHealth);
};

#endif //ENEMY_HPP
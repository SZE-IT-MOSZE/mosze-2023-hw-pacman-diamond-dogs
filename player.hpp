#ifndef PLAYER_HPP      ////j�t�kos j�jl header-e
#define PLAYER_HPP


#include "enemy.hpp"
#include "entity.hpp"


class Player : public Entity {
    private:
    int health;
    Enemy* playerTarget;
    int counter;

    public:
    Player(SDL_Renderer* renderer, std::string path, int x, int y, int initHealth);
    void SetCounter(int newcountervalue);
    int GetCounter();
    int GetHealth();
    Enemy* GetTarget();
    void SetTarget(Enemy* newTarget);
    void SetHealth(int newHealth);
};

#endif //PLAYER_HPP

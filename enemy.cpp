#include <enemy.hpp>

Enemy::Enemy(SDL_Renderer*& renderer, std::string path, int x, int y, int initHealth, std::string monsterName) : 
    Entity(renderer,path, x, y),
    health(initHealth),
    name(monsterName){}

int Enemy::GetHealth(){
    return health;
};

void Enemy::SetHealth(int newHealth){
    health = newHealth;
};
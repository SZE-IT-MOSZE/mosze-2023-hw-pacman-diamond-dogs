#include <enemy.hpp>

Enemy::Enemy(SDL_Renderer*& renderer, std::string path, int x, int y, int initHealth) : 
    Entity(renderer,path, x, y),
    health(initHealth){}

int Enemy::GetHealth(){
    return health;
};

void Enemy::SetHealth(int newHealth){
    health = newHealth;
};
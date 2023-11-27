#include <player.hpp>

Player::Player(SDL_Renderer*& renderer, std::string path, int x, int y, int initHealth) : 
    Entity(renderer,path, x, y),
    health(initHealth),
    playerTarget(nullptr){}
    
int Player::GetHealth(){
    return health;
};

void Player::SetHealth(int newHealth){
    health = newHealth;
};

void Player::SetTarget(Enemy* newTarget){
    playerTarget = newTarget;
};

void Player::SetCounter(int newcountervalue){
    counter = newcountervalue;
};

int Player::GetCounter(){
    return counter;
};
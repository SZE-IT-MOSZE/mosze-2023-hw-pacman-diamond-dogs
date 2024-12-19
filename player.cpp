#include "player.hpp"       //játékos adataival foglalkozik


Player::Player(SDL_Renderer* renderer, std::string path, int x, int y, int initHealth) : 
    Entity(renderer,path, x, y),
    health(initHealth),
    playerTarget(nullptr){
        SetRectPos(320,256);
    }

void Player::SetHealth(int newHealth){
    health = newHealth;
};

void Player::SetTarget(Enemy* newTarget){
    playerTarget = newTarget;
};

void Player::SetCounter(int newcountervalue){
    counter = newcountervalue;
};

int Player::GetHealth(){
    return health;
};

int Player::GetCounter(){
    return counter;
};

Enemy* Player::GetTarget(){
    return playerTarget;
};

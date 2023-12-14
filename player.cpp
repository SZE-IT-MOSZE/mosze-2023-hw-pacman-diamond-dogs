#include <player.hpp>
const int SCREEN_W = 640;
const int SCREEN_H = 512;
const int TEXTURE_W = 32;
const int TEXTURE_H = 32;
const int ScreenOffsetX = SCREEN_W / 2;
const int ScreenOffsetY = SCREEN_H / 2;

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
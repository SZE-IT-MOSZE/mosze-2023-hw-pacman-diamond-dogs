#include "enemy.hpp"
#include <cstdio>

Enemy::Enemy (SDL_Renderer*& renderer, std::string path, int x, int y, int initHealth, std::string monsterName) : 
    Entity (renderer,path, x, y),
    health (initHealth),
    name (monsterName){}

int Enemy::GetHealth (){
    return health;
};


void Enemy::SetHealth (int newHealth){
    health = newHealth;
};


void Enemy::Patrol (std::vector<std::vector<int>> map) {

    int latestX = GetXPos ();
    int latestY = GetYPos ();

    switch (heading) {

        case up:
            if (NextTileIsFree (map[latestY + 1][latestX])){
                MoveEntity (latestX, latestY + 1);
                UpdateEntityPos(GetYPos (), GetYPos ());
            } else {
                heading = GetRandomDirection ();
            }
            break;

        case right:
            if (NextTileIsFree (map[latestY][latestX + 1])) {
                MoveEntity (latestX + 1, latestY);
                UpdateEntityPos(GetXPos (), GetYPos ());
            } else {
                heading = GetRandomDirection ();
            }
            break;

        case down:
            if (NextTileIsFree (map[latestY - 1][latestX])) {
                MoveEntity (latestX, latestY - 1);
                UpdateEntityPos(GetXPos (), GetYPos ());
            } else {
                heading = GetRandomDirection ();
            }
            break;

        case left:
            if  (NextTileIsFree(map[latestY][latestX - 1])) {
                MoveEntity (latestX - 1, latestY);
                UpdateEntityPos(GetXPos (), GetYPos ());
            } else {
                heading = GetRandomDirection ();
            }
            break;

        default:
            heading = GetRandomDirection();
            break;
    } // switch
}


bool Enemy::NextTileIsFree(int tile){
    if (tile == 2) return true;

    return false;
}

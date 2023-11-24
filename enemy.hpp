#include <entity.hpp>

class Enemy : public Entity {
    private:
    int health;

    public:
    Enemy(SDL_Renderer*& renderer, std::string path, int x, int y, int initHealth);
    int GetHealth();
    void SetHealth(int newHealth);
};
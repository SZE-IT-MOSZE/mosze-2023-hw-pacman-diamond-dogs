#include <SDL.h>
#include <string>

class Entity {
    private:
    SDL_Texture* entityTexture;
    SDL_Rect entityRect;
    int xPos;
    int yPos;
    
    public:
    Entity(SDL_Renderer*& renderer, std::string path, int x, int y);
    ~Entity();
    void RenderEntity(SDL_Renderer*& renderer);
    void MoveEntity(int x, int y);
    void UpdateEntityPos(int charXPos, int charYPos);
    int GetXPos();
    int GetYPos();
};
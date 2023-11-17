#include <SDL.h>
#include <string>
class TextureRect
{
    private:
    SDL_Rect rectangle;
    SDL_Texture* texture;

    public:
    TextureRect(SDL_Renderer*& renderer, std::string path, int xPos, int yPos, int* xOffset, int* yOffset);
    ~TextureRect();
    void RenderTextureRect(SDL_Renderer*& renderer);
};
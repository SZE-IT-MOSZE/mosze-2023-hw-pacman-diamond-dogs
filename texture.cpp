#include <SDL.h>
#include <texture.h>
#include <texturelist.h>
#include <string>
#define TEXTURE_W 32
#define TEXTURE_H 32
TextureRect::TextureRect(SDL_Renderer*& renderer, std::string path, int xPos, int yPos, int* xOffset, int* yOffset)
{
    rectangle.x = (xPos - (*xOffset * TEXTURE_W));
    rectangle.y = (yPos - (*yOffset * TEXTURE_H));
    rectangle.w = TEXTURE_W;
    rectangle.h = TEXTURE_H;
    SDL_Surface* surfaceFromList = TextureList::GetInstance().GetSurface(path);
    texture = SDL_CreateTextureFromSurface(renderer, surfaceFromList);
}
TextureRect::~TextureRect()
{
    SDL_DestroyTexture(texture);
}
void TextureRect::RenderTextureRect(SDL_Renderer*& renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &rectangle);
}
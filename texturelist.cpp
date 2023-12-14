#include "texturelist.h"
#include "SDL.h"
TextureList::TextureList()
{

}
TextureList::TextureList(TextureList const&)
{

}
TextureList TextureList::operator=(TextureList const& rhs)
{
    return *this;
}
TextureList& TextureList::GetInstance()
{
    static TextureList* instance = new TextureList;
    return *instance;
}
SDL_Surface* TextureList::GetTexture(std::string path, SDL_Renderer*& renderer)
{
    
    if (texturemap.find(path) == texturemap.end())
        {
            SDL_Surface* surface = SDL_LoadBMP(path.c_str());
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
            SDL_FreeSurface(surface);
            texturemap.insert(std::make_pair(path,texture));
        }
    return (texturemap.find(path))->second;
}

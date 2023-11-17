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
SDL_Surface* TextureList::GetSurface(std::string path)
{
    
    if (surfacemap.find(path) == surfacemap.end())
        {
            SDL_Surface* surface = SDL_LoadBMP(path.c_str());
            surfacemap.insert(std::make_pair(path,surface));
        }
    return (surfacemap.find(path))->second;
}

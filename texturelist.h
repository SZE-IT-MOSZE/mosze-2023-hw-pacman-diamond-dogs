#include <string>
#include <unordered_map>
#include <SDL.h>
class TextureList
{
    private:
    TextureList();
    TextureList(TextureList const&);
    TextureList operator=(TextureList const&);

    std::unordered_map<std::string, SDL_Surface*> surfacemap;
    public:
    static TextureList& GetInstance();
    SDL_Surface* GetSurface(std::string path);
};
#include <string>
#include <unordered_map>
#include <SDL.h>
class TextureList
{
    private:
    TextureList();
    TextureList(TextureList const&);
    TextureList operator=(TextureList const&);

    std::unordered_map<std::string, SDL_Texture*> texturemap;
    public:
    static TextureList& GetInstance();
    SDL_Texture* GetTexture(std::string path);
};
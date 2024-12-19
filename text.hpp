#ifndef TEXT_HPP        //text fájl header-je
#define TEXT_HPP


// from stdlib
#include <string>

// from SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Text {
    private:
    SDL_Rect rect;
    SDL_Surface* surface;
    SDL_Texture* texture;
    TTF_Font* font;
    static bool ttf_init;

    public:
    Text(std::string fontfilepath, int fontsize);
    ~Text();
    void DrawText(SDL_Renderer* renderer, std::string text, int xpos, int ypos, int width, int height);
};

#endif //TEXT_HPP

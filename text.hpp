#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

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
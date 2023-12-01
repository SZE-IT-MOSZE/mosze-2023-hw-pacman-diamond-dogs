#include <text.hpp>
#include <iostream>

bool Text::ttf_init = false;

Text::Text(std::string fontfilepath, int fontsize){
    // Just like when we initialize our graphics subsystem,
    // we need to do the same for our font system.         	
    if(!ttf_init){
        ttf_init = true;
    }  
    font = TTF_OpenFont(fontfilepath.c_str(),fontsize);
    if(font == nullptr){
        std::cout << "font loading error" << std::endl;
        exit(1);
    }
}

Text::~Text(){
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void Text::DrawText(SDL_Renderer* renderer, std::string text, int xpos, int ypos, int width, int height){
    surface = TTF_RenderText_Solid(font,text.c_str(),{255,255,255});
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);
    rect.x = xpos;
    rect.y = ypos;
    rect.w = width;
    rect.h = height;
    // Render our text on a rectangle
    SDL_RenderCopy(renderer,texture,NULL,&rect);

}
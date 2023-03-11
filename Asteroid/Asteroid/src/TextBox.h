#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

class InputBox 
{
public:
    InputBox(SDL_Renderer* renderer, int x, int y, int w, int h, std::string font_path, int font_size, SDL_Color font_color, SDL_Color background_color); 


    ~InputBox();

    void handleEvent(SDL_Event& event);
    

    void setText(std::string text);
    

    void render();

private:
    SDL_Renderer* m_renderer;
    SDL_Rect m_rect;
    std::string m_font_path;
    int m_font_size;
    SDL_Color m_font_color;
    SDL_Color m_background_color;
    TTF_Font* m_font;
    std::string m_text;
    SDL_Surface* m_surface;
    SDL_Texture* m_texture;

    bool active = false;
    int lenght = 10;
};
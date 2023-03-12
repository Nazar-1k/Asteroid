#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

class Text
{
public:
    Text(int x, int y, SDL_Renderer* renderer, std::string text, int size, SDL_Color textColor);
    ~Text();

    void draw();
    void draw(int a);
    int getWidth() { return textSurface->w; }
    int getHeight() { return textSurface->h; }

    void SetText(std::string text);

    void setAlpha(Uint8 alpha);
    
    void setPosition(int x, int y);
    void setTextColor(SDL_Color textColor);

private:
    int m_x, m_y;
    SDL_Renderer* m_renderer;

    TTF_Font* m_font;
    std::string m_text;

    SDL_Rect m_rect;

    SDL_Color m_textColor;

    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
};


#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <fstream>
#include <string>

class InputBox 
{
public:
    InputBox(SDL_Renderer* renderer, int x, int y, int w, int h, std::string font_path, int font_size, SDL_Color font_color, SDL_Color background_color, std::string& name);


    ~InputBox();

    void handleEvent(SDL_Event& event, std::string& name);

    std::string setName(std::string filename);
    void writeLineToFile(std::string filename, std::string line);

    void setText(std::string text);
    std::string getText() { return m_text; }
    

    void render(std::string name);

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
    bool write;
    int lenght = 10;
};
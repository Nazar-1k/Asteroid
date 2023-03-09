#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Text.h"
#include <iostream>
#include <string>
#include "Sprite.h"

class Button {
public:
    Button(SDL_Renderer* renderer, std::string text, SDL_Rect rect);
    Button(SDL_Renderer* renderer, int x, int y, std::string text,int size, SDL_Color clorText);
    Button(SDL_Renderer* renderer, std::string text, int x, int y, const char path[], SDL_Color clor);
    Button(SDL_Renderer* renderer, int x, int y, const char path[]);
    ~Button();
       
    void handleEvent(const SDL_Event& event, float mouseX, float mouseY);
    
    void draw();
    void draw(Uint8 alpha);
    void drawSpriteButton();
    void drawTextButton();

    bool isMouseOver(float mouseX, float mouseY) const;
    bool isPressed() const;

    void setPosition(int x, int y);

    int getWidth() { return m_rect.w; }
    int getHeight() { return m_rect.h; }

    void setTextColor(SDL_Color textColor);
    void setText(std::string text);

    void setRectColor(SDL_Color rectColor);
    void setHovered(bool hovered);

private:
    SDL_Renderer* m_renderer;

    TTF_Font* m_font;
    std::string m_text;

    SDL_Rect m_rect;
    SDL_Rect m_rect_bottom;

    SDL_Color m_textColor;
    SDL_Color m_rectColor;


    std::unique_ptr<Text> text_b;
    std::unique_ptr<Sprite> sprite_b;

    bool m_hovered = false;
    SDL_Color m_hoveredRectColor;
    bool m_isPressed;

    bool active = false;

    

};



#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

class Button {
public:
    Button(SDL_Renderer* renderer, std::string text, SDL_Rect rect);
       
    void handleEvent(const SDL_Event& event, float mouseX, float mouseY);
    
    void draw();
    bool isMouseOver(float mouseX, float mouseY) const;
    bool isPressed() const;

    void setPosition(int x, int y);

    void setTextColor(SDL_Color textColor);
    void setText(std::string text);

    void setRectColor(SDL_Color rectColor);
    void setHovered(bool hovered);

private:
    SDL_Renderer* m_renderer;
    TTF_Font* m_font;
    std::string m_text;
    SDL_Rect m_rect;
    SDL_Color m_textColor;
    SDL_Color m_rectColor;
    bool m_hovered = false;
    SDL_Color m_hoveredRectColor;
    bool m_isPressed;
};

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

class Button {
public:
    Button(SDL_Renderer* renderer, std::string text, SDL_Rect rect, int radius = 0);
    ~Button();
       
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

    void drawRoundedRect(SDL_Renderer* renderer, SDL_Rect rect, int radius) const {
        int x = rect.x;
        int y = rect.y;
        int w = rect.w;
        int h = rect.h;
        
        SDL_SetRenderDrawColor(renderer, m_rectColor.r, m_rectColor.g, m_rectColor.b, m_rectColor.a);
        SDL_RenderDrawLine(renderer, x + radius, y, x + w - radius, y);
        SDL_RenderDrawLine(renderer, x + radius, y + h, x + w - radius, y + h);
        SDL_RenderDrawLine(renderer, x, y + radius, x, y + h - radius);
        SDL_RenderDrawLine(renderer, x + w, y + radius, x + w, y + h - radius);

        drawCircle(renderer, x + radius, y + radius, radius);
        drawCircle(renderer, x + w - radius, y + radius, radius);
        drawCircle(renderer, x + radius, y + h - radius, radius);
        drawCircle(renderer, x + w - radius, y + h - radius, radius);
    }

    void drawCircle(SDL_Renderer* renderer, int x, int y, int radius) const {
        int d = 3 - 2 * radius;
        int posX = 0;
        int posY = radius;

        while (posX <= posY) {
            SDL_RenderDrawPoint(renderer, x + posX, y + posY);
            SDL_RenderDrawPoint(renderer, x - posX, y + posY);
            SDL_RenderDrawPoint(renderer, x + posX, y - posY);
            SDL_RenderDrawPoint(renderer, x - posX, y - posY);
            SDL_RenderDrawPoint(renderer, x + posY, y + posX);
            SDL_RenderDrawPoint(renderer, x - posY, y + posX);
            SDL_RenderDrawPoint(renderer, x + posY, y - posX);
            SDL_RenderDrawPoint(renderer, x - posY, y - posX);

            if (d < 0) {
                d += 4 * posX + 6;
            }
            else {
                d += 4 * (posX - posY) + 10;
                posY--;
            }
            posX++;
        }
    }

    

    SDL_Renderer* m_renderer;
    /*int m_x, m_y, m_w, m_h;*/
    int m_radius;

    TTF_Font* m_font;
    std::string m_text;

    SDL_Rect m_rect;

    SDL_Color m_textColor;
    SDL_Color m_rectColor;

    bool m_hovered = false;
    SDL_Color m_hoveredRectColor;
    bool m_isPressed;

    SDL_Texture* m_textTexture;
    int m_textW, m_textH;

};

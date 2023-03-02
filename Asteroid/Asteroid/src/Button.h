#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Button {
public:
    Button(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Rect rect)
        : m_renderer(renderer), m_font(font), m_text(text), m_rect(rect), m_textColor({ 0, 0, 0, 255 }), m_rectColor({ 255, 255, 255, 255 }), m_hoveredRectColor({ 200, 200, 200, 255 }) {}
   /* ~Button()
    {
      
    }*/
    void draw() {
        // Draw button rectangle
        SDL_SetRenderDrawColor(m_renderer, m_rectColor.r, m_rectColor.g, m_rectColor.b, m_rectColor.a);
        if (m_hovered) {
            SDL_SetRenderDrawColor(m_renderer, m_hoveredRectColor.r, m_hoveredRectColor.g, m_hoveredRectColor.b, m_hoveredRectColor.a);
        }
        SDL_RenderFillRect(m_renderer, &m_rect);

        // Draw text in button
        SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

        int textWidth = textSurface->w;
        int textHeight = textSurface->h;
        int x = m_rect.x + (m_rect.w - textWidth) / 2;
        int y = m_rect.y + (m_rect.h - textHeight) / 2;

        SDL_Rect textRect = { x, y, textWidth, textHeight };
        SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);

        // Clean up
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    void setPosition(int x, int y) {
        m_rect.x = x;
        m_rect.y = y;
    }

    bool isMouseOver(int mouseX, int mouseY) {
        return (mouseX >= m_rect.x && mouseX <= m_rect.x + m_rect.w &&
            mouseY >= m_rect.y && mouseY <= m_rect.y + m_rect.h);
    }

    void setTextColor(SDL_Color textColor) {
        m_textColor = textColor;
    }

    void setRectColor(SDL_Color rectColor) {
        m_rectColor = rectColor;
    }

    void setHovered(bool hovered) {
        m_hovered = hovered;
    }

private:
    SDL_Renderer* m_renderer;
    TTF_Font* m_font;
    std::string m_text;
    SDL_Rect m_rect;
    SDL_Color m_textColor;
    SDL_Color m_rectColor;
    bool m_hovered = false;
    SDL_Color m_hoveredRectColor;
};

#include "Button.h"

static const char path[] = "font/TerminatorCyr.ttf";

Button::Button(SDL_Renderer* renderer, std::string text, SDL_Rect rect, int radius)
    : m_renderer(renderer), m_text(text), m_rect(rect), m_textColor({ 0, 0, 0, 255 }),
    m_rectColor({ 255, 255, 255, 255 }), m_hoveredRectColor({ 200, 200, 200, 255 }), m_radius(radius)
{
    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error:\n" << TTF_GetError();
    }

    // Font Path


    // Create a font
    m_font = TTF_OpenFont(path, 24);

    if (!m_font)
    {
        std::cout << "Unable to load font " << path << " SDL_image Error : \n" << TTF_GetError() << std::endl;
    }
}
Button::~Button()
{
    if (m_textTexture != nullptr) {
        SDL_DestroyTexture(m_textTexture);
    }
    TTF_CloseFont(m_font);
}
void Button::draw()
{


    SDL_SetRenderDrawColor(m_renderer, m_rectColor.r, m_rectColor.g, m_rectColor.b, m_rectColor.a);
    if (m_hovered) 
    {
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

void Button::setPosition(int x, int y)
{
    m_rect.x = x;
    m_rect.y = y;
}

bool Button::isMouseOver(float mouseX, float mouseY) const  
{
    return (mouseX >= m_rect.x && mouseX <= m_rect.x + m_rect.w &&
        mouseY >= m_rect.y && mouseY <= m_rect.y + m_rect.h);
}

bool Button::isPressed() const
{
    return m_isPressed;
}

void Button::handleEvent(const SDL_Event& event, float mouseX, float mouseY)  
{
    switch (event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
            if (isMouseOver(mouseX, mouseY))
                m_isPressed = true;
        break;

    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT)
            m_isPressed = false;
        break;
    case SDL_MOUSEMOTION:
    {
        // Check if the mouse is over the button and set its hovered state accordingly
        if (isMouseOver(mouseX, mouseY))
            m_hovered = true;
        else
            m_hovered = false;
    }
    }
}

void Button::setTextColor(SDL_Color textColor)
{
    m_textColor = textColor;
}

void Button::setText(std::string text)
{
    m_text = text;
}

void Button::setRectColor(SDL_Color rectColor)
{
    m_rectColor = rectColor;
}

void Button::setHovered(bool hovered)
{
    m_hovered = hovered;
}


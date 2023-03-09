#include "Button.h"

static const char path[] = "font/TerminatorCyr.ttf";

Button::Button(SDL_Renderer* renderer, std::string text, SDL_Rect rect)
    : m_renderer(renderer), m_text(text), m_rect(rect), m_textColor({ 0, 0, 0, 255 })
{
    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error:\n" << TTF_GetError();
    }

    // Font Path


    // Create a font
    m_font = TTF_OpenFont(path, 45);

    if (!m_font)
    {
        std::cout << "Unable to load font " << path << " SDL_image Error : \n" << TTF_GetError() << std::endl;
    }

    m_rect.x -= m_rect.w / 2;
    m_rect.y -= m_rect.h / 2;

    m_rect_bottom = { m_rect.x + 10, m_rect.y + 10, m_rect.w, m_rect.h };
}

Button::Button(SDL_Renderer* renderer, int x, int y, std::string text,int size, SDL_Color colorText)
    : m_renderer(renderer), m_text(text), m_textColor(colorText)
{
    text_b = std::unique_ptr<Text>(new Text{ x , y  , m_renderer , m_text, size , { 0, 0, 0, 255 } });
    if (!text_b)
    {
        std::cout << "123123123";
   }
    m_rect = { x,y,text_b->getWidth(), text_b->getHeight() };
    
    m_rect.x -= m_rect.w / 2;
    m_rect.y -= m_rect.h / 2;
}

Button::Button(SDL_Renderer* renderer, std::string text, int x, int y, const char path[], SDL_Color color)
    : m_renderer(renderer), m_text(text)
{
    
    sprite_b = std::unique_ptr<Sprite>(new Sprite{ path , renderer });
    

    text_b = std::unique_ptr<Text>(new Text{ x + sprite_b->getWidth() + 30 , y  , m_renderer , m_text, 45 , color });
    sprite_b->setHeight(text_b->getHeight());
    
    m_rect = { x,y,(sprite_b->getWidth() + text_b->getWidth() + 30), (sprite_b->getHeight() ) };
    m_rect.x -= m_rect.w / 2;
    m_rect.y -= m_rect.h / 2;

    sprite_b->setX(static_cast<float>(m_rect.x));
    sprite_b->setY(static_cast<float>(m_rect.y));

    text_b->setPosition(static_cast<int>(m_rect.x + sprite_b->getWidth() + 30), static_cast<int>(m_rect.y));
}

Button::Button(SDL_Renderer* renderer, int x, int y, const char path[])
{
    sprite_b = std::unique_ptr<Sprite>(new Sprite{ path , renderer });
    sprite_b->setX(static_cast<float>(x));
    sprite_b->setY(static_cast<float>(y));
    m_rect = { static_cast<int>(sprite_b->getX()), static_cast<int>(sprite_b->getY()), sprite_b->getWidth(),  sprite_b->getHeight() };

    m_rect.x -= m_rect.w / 2;
    m_rect.y -= m_rect.h / 2;
    
    sprite_b->setX(static_cast<float>(m_rect.x));
    sprite_b->setY(static_cast<float>(m_rect.y));

}

Button::~Button()
{
    TTF_CloseFont(m_font);
}

void Button::draw()
{
    SDL_SetRenderDrawColor(m_renderer, 63, 48, 183, m_rectColor.a);
    SDL_RenderFillRect(m_renderer, &m_rect_bottom);

    SDL_SetRenderDrawColor(m_renderer,  m_rectColor.r,  m_rectColor.g,  m_rectColor.b, m_rectColor.a);
    if (m_hovered) 
    {
        if (SDL_GetTicks() % 5)
        {
            m_rect.x += 1;
            m_rect.y += 1;
        }
        if (m_rect.x >= m_rect_bottom.x - 5)
            m_rect.x = m_rect_bottom.x - 5;
        if (m_rect.y >= m_rect_bottom.y - 5)
            m_rect.y = m_rect_bottom.y - 5;

      
        SDL_SetRenderDrawColor(m_renderer, 55, 116, 224, 255);
    }
    else
    {
        if (SDL_GetTicks() % 5)
        {
            m_rect.x -= 1;
            m_rect.y -= 1;
        }
        if (m_rect.x <= m_rect_bottom.x - 10)
            m_rect.x = m_rect_bottom.x - 10 ;
        if (m_rect.y <= m_rect_bottom.y - 10)
            m_rect.y = m_rect_bottom.y - 10;
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

void Button::draw(Uint8 alpha)
{
    if (m_hovered)
    {
        text_b->setTextColor({ 60, 88, 160, alpha });
        sprite_b->setAlpha(alpha);
    }
    else
    {
        text_b->setTextColor({ 60, 88, 160, 255 });
        sprite_b->setAlpha(255);
    }
    
    text_b->draw(alpha);
    sprite_b->render();

}

void Button::drawSpriteButton()
{
    sprite_b->setY(static_cast<float>(m_rect.y));
    sprite_b->setX(static_cast<float>(m_rect.x));

    if (m_hovered)
    {
        sprite_b->setAlpha(200);
    }
    else
    {
        sprite_b->setAlpha(255);
    }
    sprite_b->render();
}

void Button::drawTextButton()
{
    if (active)
    {
        text_b->setTextColor({ 1, 1, 255, 255 });
    }
    if (m_hovered and !active)
    {
        text_b->setTextColor({ 255, 255, 255, 100 });
      
    }
    else if(!m_hovered and !active)
    {
        text_b->setTextColor({ 255, 255, 255, 255 });
    }
    text_b->draw();
  
}

void Button::setPosition(int x, int y)
{
    m_rect.x = x - m_rect.w / 2;
    m_rect.y = y - m_rect.h / 2;
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


#include "Text.h"

static const char path[] = "font/TerminatorCyr.ttf";

Text::Text(int x, int y, SDL_Renderer* renderer, std::string text, int size, SDL_Color textColor)
    :m_x(x), m_y(y), m_renderer(renderer), m_text(text), m_textColor(textColor), m_rect({ 0,0,0,0 })
{
    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error:\n" << TTF_GetError();
    }
    // Create a font
    m_font = TTF_OpenFont(path, size);

    if (!m_font)
    {
        std::cout << "Unable to load font " << path << " SDL_image Error : \n" << TTF_GetError() << std::endl;
    }  
    textSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_textColor);
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
  
}

Text::~Text()
{
    TTF_CloseFont(m_font);
}

void Text::draw() 
{
    textSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_textColor);
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

    m_rect = { m_x - textSurface->w / 2 , m_y - textSurface->h / 2, textSurface->w , textSurface->h };
    SDL_RenderCopy(m_renderer, textTexture, NULL, &m_rect);
}
void Text::draw(int a)
{
    textSurface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_textColor);
    textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

    m_rect = { m_x  , m_y , textSurface->w , textSurface->h };
    SDL_RenderCopy(m_renderer, textTexture, NULL, &m_rect);
}

void Text::setAlpha(Uint8 alpha)
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod(textTexture, alpha);
}

void Text::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

void Text::setTextColor(SDL_Color textColor)
{
    m_textColor = textColor;
}

void Text::SetText(std::string text)
{
    m_text = text;
}

#include "TextBox.h"

InputBox::InputBox(SDL_Renderer* renderer, int x, int y, int w, int h, std::string font_path, int font_size, SDL_Color font_color, SDL_Color background_color)
{

    // Initialize member variables
    m_renderer = renderer;
    m_rect = { x, y, w, h };
    m_font_path = font_path;
    m_font_size = font_size;
    m_font_color = font_color;
    m_background_color = background_color;

    // Load font
    m_font = TTF_OpenFont(font_path.c_str(), font_size);
    if (!m_font) {
        // Handle font load failure
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }
    // Initialize surface and texture
    m_surface = SDL_CreateRGBSurface(0, m_rect.w, m_rect.h, 32, 0, 0, 0, 0);
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);

    // Set initial text
    setText(" ");
}

InputBox::~InputBox() {
    // Cleanup
    TTF_CloseFont(m_font);
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);
}

void InputBox::handleEvent(SDL_Event& event)
{
    // Handle input events
    if (active && event.type == SDL_TEXTINPUT)
    {
        // Append character to text
        if (m_text.length() <= lenght)
        {
            m_text += event.text.text;
            setText(m_text);

        }
    }
    else if (active && event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_BACKSPACE && m_text.length() > 1) {
            // Remove last character from text
            m_text.pop_back();
            setText(m_text);

        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        if (mouseX >= m_rect.x && mouseX <= m_rect.x + m_rect.w &&
            mouseY >= m_rect.y && mouseY <= m_rect.y + m_rect.h)
        {
            active = true;
        }
        else
        {
            active = false;
        }

    }
}

void InputBox::setText(std::string text)
{
    // Set text and render onto surface
    m_text = text;
    if (active)
        SDL_FillRect(m_surface, NULL, SDL_MapRGBA(m_surface->format, m_background_color.r, m_background_color.g, m_background_color.b - 50, 255));
    else
        SDL_FillRect(m_surface, NULL, SDL_MapRGBA(m_surface->format, m_background_color.r, m_background_color.g, m_background_color.b, m_background_color.a));
    SDL_Surface* text_surface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_font_color);
    SDL_Rect text_rect = { 0, 0, text_surface->w, text_surface->h };

    SDL_BlitSurface(text_surface, NULL, m_surface, &text_rect);
    SDL_FreeSurface(text_surface);

    // Update texture
    SDL_DestroyTexture(m_texture);
    m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
}

void InputBox::render() {
    // Render texture onto renderer
    if (m_text.length() == 1 && !active)
    {
        setText(" Input Name");
    }
    if (active)
    {
        if (m_text == " Input Name")
        {
            setText(" ");
        }
        else
        {
            setText(m_text);
        }

    }
    if (!active)
    {

        setText(m_text);
    }

    SDL_RenderCopy(m_renderer, m_texture, NULL, &m_rect);
    SDL_SetRenderDrawColor(m_renderer, 1, 1, 1, 255);
    SDL_RenderDrawRect(m_renderer, &m_rect);

}

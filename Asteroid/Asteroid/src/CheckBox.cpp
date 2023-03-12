#include "CheckBox.h"


CheckBox::CheckBox(SDL_Renderer* renderer, int x, int y, int w, int h)
    : m_rect({ x, y, w, h }), m_isChecked(false), m_renderer(renderer) {}

bool CheckBox::isChecked() const {
    return m_isChecked;
}

void CheckBox::setChecked(bool isChecked)
{
    m_isChecked = isChecked;
}

void CheckBox::render() {
    if (!m_isChecked)
    {
    SDL_SetRenderDrawColor(m_renderer, 55, 116, 224,255);
    SDL_RenderFillRect(m_renderer, &m_rect);

    SDL_SetRenderDrawColor(m_renderer, 255, 1, 1, 255);
    SDL_RenderDrawRect(m_renderer, &m_rect);

    }
    if (m_isChecked) 
    {
        SDL_SetRenderDrawColor(m_renderer, 55, 116, 224-50, 255);
        SDL_RenderFillRect(m_renderer, &m_rect);

        SDL_SetRenderDrawColor(m_renderer, 1, 255, 1, 255);
        SDL_RenderDrawLine(m_renderer, m_rect.x, m_rect.y, m_rect.x + m_rect.w, m_rect.y + m_rect.h);
        SDL_RenderDrawLine(m_renderer, m_rect.x, m_rect.y + m_rect.h, m_rect.x + m_rect.w, m_rect.y);
    }
}

bool CheckBox::handleEvent(const SDL_Event& event) {
    switch (event.type) {
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
            int mouseX = event.button.x;
            int mouseY = event.button.y;
            if (mouseX >= m_rect.x && mouseX <= m_rect.x + m_rect.w &&
                mouseY >= m_rect.y && mouseY <= m_rect.y + m_rect.h)
            {
                m_isChecked = !m_isChecked;
                return true;
            }
        }
        break;
    default:
        break;
    }
    return false;
}

#pragma once

#include <SDL.h>

class CheckBox {
public:
    CheckBox(SDL_Renderer* renderer, int x, int y, int w, int h);
  
    bool isChecked() const;
    void setChecked(bool isChecked);
    void render() ;
    bool handleEvent(const SDL_Event& event);

private:
    SDL_Rect m_rect;
    bool m_isChecked;
    SDL_Renderer* m_renderer;
};

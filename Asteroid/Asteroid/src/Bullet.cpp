#include "Bullet.h"
#include "Asteroid.h"

Bullet::Bullet(const char* path, SDL_Renderer* renderer)
    : Sprite(path, renderer)
{
    x = 100;
    y = 110;
}


void Bullet::poolEvent(SDL_Event& event)
{


}

void Bullet::render(SDL_Rect* clip, float angle, SDL_Point* center, SDL_RendererFlip flip)
{
    angle = this->angle;
  
    this->angle = angle;
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { static_cast<int>(x - width / 2),  static_cast<int>(y - height / 2), width/20, height/20 };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    float fx, fy;
    if (teleport(fx, fy, 1000, 600))
    {

        SDL_Rect renderQuad2 = { static_cast<int>(fx - width / 2),  static_cast<int>(fy - height / 2), width / 20, height / 20 };
        if (clip != NULL)
        {
            renderQuad2.w = clip->w;
            renderQuad2.h = clip->h;
        }
        //Render to screen   
        SDL_RenderCopyEx(renderer, texture, clip, &renderQuad2, angle, center, SDL_FLIP_HORIZONTAL);
    }

    //Render to screen
    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, SDL_FLIP_HORIZONTAL);
   


}

void Bullet::move()
{
}

bool Bullet::colideAsteroid(Asteroid& ast)
{
    return false;
}

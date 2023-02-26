#include "Asteroid.h"

Asteroid::Asteroid(const char* path, SDL_Renderer* renderer)
    : Sprite(path, renderer), to_be_deleted(false)
{
	dx =  sin(rand() % 361 * 3.14159 / 180) * velocity;
	dy = -cos(rand() % 361 * 3.14159 / 180) * velocity;
}

void Asteroid::move()
{
    x += dx;
    y += dy;

#pragma endregion

#pragma region MaxSpeed
    if (dx >= maxVelocity)
        dx = maxVelocity;
    else if (dx <= -maxVelocity)
        dx = -maxVelocity;

    if (dy >= maxVelocity)
        dy = maxVelocity;
    else if (dy <= -maxVelocity)
        dy = -maxVelocity;
}

void Asteroid::render(SDL_Rect* clip, float angle, SDL_Point* center, SDL_RendererFlip flip)
{
    this->angle = angle;
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { static_cast<int>(x - width / 2),  static_cast<int>(y - height / 2), width, height };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    float fx, fy;
    if (teleport(fx, fy, 1000, 600))
    {

        SDL_Rect renderQuad2 = { static_cast<int>(fx - width / 2),  static_cast<int>(fy - height / 2), width, height };
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
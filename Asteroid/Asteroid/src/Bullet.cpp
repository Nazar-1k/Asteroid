#include "Bullet.h"
#include "Asteroid.h"
#include "Arrow.h"
#include "SpaceShip.h"

static const char path[] = "data/Bullet/bullet.png";

Bullet::Bullet(SDL_Renderer* renderer, Ship& ship, Arrow& arrow)
{
    initSprite(path, renderer);
    creatBullet(ship, arrow);
}
Bullet::Bullet(SDL_Renderer* renderer, Ship& ship)
{
    initSprite(path, renderer);
    creatBullet(ship);
}

void Bullet::render(SDL_Rect* clip, float angle, SDL_Point* center, SDL_RendererFlip flip)
{
    if (is_bullet_active)
    {
        angle = this->angle;

        //Set rendering space and render to screen
        SDL_Rect renderQuad = { static_cast<int>(x),  static_cast<int>(y), width / 20, height / 20 };

        //Set clip rendering dimensions
        if (clip != NULL)
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        //Render to screen
        SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, SDL_FLIP_HORIZONTAL);
    }


}

void Bullet::creatBullet(Ship& Ship, Arrow& arrow)
{
    x = Ship.x;
    y = Ship.y;

    dx = arrow.x - Ship.x;
    dy = arrow.y - Ship.y;
    angle = static_cast<float>(atan2(dy, dx) / M_PI*180);

    float angle = atan2(dy, dx);

    dx = bulletSpeed * cos(angle);
    dy = bulletSpeed * sin(angle);

    is_bullet_active = true;
}

void Bullet::creatBullet(Ship& Ship)
{
    x = Ship.x;
    y = Ship.y;
    angle = Ship.angle * 3.14159 / 180;

    dx = static_cast<float>(sin(angle ) * bulletSpeed );
    dy = static_cast<float>(-cos(angle ) * bulletSpeed );

    angle = static_cast<float>(atan2(dy, dx) / M_PI * 180);
    is_bullet_active = true;
}

void Bullet::move(int w_screen, int h_screen)
{
    if (is_bullet_active)
    {
       
        x += dx;
        y += dy;

        if (x < 0 || x > w_screen)
            is_bullet_active = false;

        if (y < 0 || y > h_screen)
            is_bullet_active = false;
    }
}

bool Bullet::colideAsteroid(Asteroid& ast)
{
    float fx = ast.x - x;
    float fy = ast.y - y;

    return  std::sqrt(fx * fx + fy * fy) <= ast.radius + height / 20;
}

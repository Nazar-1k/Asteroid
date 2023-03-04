#include "Asteroid.h"
#include <cmath>

static const char pathBigAsteroid[] = "data/Asteroids/big_asteroid.png";
static const char pathSmallAsteroid[] = "data/Asteroids/small_asteroid.png";

Asteroid::Asteroid(int x , int y, float angle, int mass, SDL_Renderer* renderer)
    : to_be_deleted(false), mass(mass),
    speedrotation(static_cast<float>((rand() % (999 - 100) + 100) / static_cast<float>(1000)))
{
    setRenderer(renderer);
    if (mass == 3)
        loadFromFile(pathSmallAsteroid);
    else if(mass == 4)
        loadFromFile(pathBigAsteroid);

    if (!this->isEmpty())
    {
        std::cout << "Asteroid ERRoR: \n" << std::endl;
    }

    dx += static_cast<float>(sin(angle * 3.14159 / 180) * velocity);
    dy += static_cast<float>(-cos(angle * 3.14159 / 180) * velocity);
    this->x = x;
    this->y = y;
   
    radius = static_cast<float>(width / 2);
    
    b_rotation = rand() % 2;
}

Asteroid::~Asteroid()
{

}

void Asteroid::move()
{
    if (!to_be_deleted)
    {
        x += dx;
        y += dy;

        if (dx >= maxVelocity)
            dx = maxVelocity;
        else if (dx <= -maxVelocity)
            dx = -maxVelocity;

        if (dy >= maxVelocity)
            dy = maxVelocity;
        else if (dy <= -maxVelocity)
            dy = -maxVelocity;

        if (b_rotation)
            angle += speedrotation;
        else
            angle -= speedrotation;
    }
  
}

void Asteroid::deleteAsteroid()
{
    to_be_deleted = true;

}

void Asteroid::render(SDL_Rect* clip, float angle, SDL_Point* center, SDL_RendererFlip flip)
{
    angle = this->angle;
    if (!to_be_deleted)
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
}

bool Asteroid::checkColition(Asteroid& asteroid1, Asteroid& asteroid2)
{
    float fx = asteroid1.x - asteroid2.x;
    float fy = asteroid1.y - asteroid2.y;

    return  std::sqrt(fx * fx + fy * fy) <= asteroid1.radius + asteroid2.radius;
}

void Asteroid::reflectingAsteroids(Asteroid& asteroid1, Asteroid& asteroid2)
{
    // Calculate the angle of collision
    float angle = atan2(asteroid1.getY() - asteroid2.getY(), asteroid1.getX() - asteroid2.getX());

    // Calculate the new velocities after the collision
    float velocity1 = std::sqrt(asteroid1.dx* asteroid1.dx + asteroid1.dy* asteroid1.dy);
    float velocity2 = std::sqrt(asteroid2.dx * asteroid2.dx + asteroid2.dy * asteroid2.dy);

    float direction1 = atan2(asteroid1.dy, asteroid1.dx);
    float direction2 = atan2(asteroid2.dy, asteroid2.dx);

    // Calculate the new velocities after the collision, taking into account the masses of the asteroids
    float newVelocity1 = (velocity1 * (asteroid1.mass - asteroid2.mass) + 2 * asteroid2.mass * velocity2) / (asteroid1.mass + asteroid2.mass);
    float newVelocity2 = (velocity2 * (asteroid2.mass - asteroid1.mass) + 2 * asteroid1.mass * velocity1) / (asteroid1.mass + asteroid2.mass);

    float newDirection1 = direction1 - angle;
    float newDirection2 = direction2 - angle;

    asteroid1.dx = static_cast<float>(newVelocity1 * cos(newDirection1) + velocity1 * sin(direction1 - angle) * cos(angle + M_PI / 2));
    asteroid1.dy = static_cast<float>(newVelocity1 * sin(newDirection1) + velocity1 * sin(direction1 - angle) * sin(angle + M_PI / 2));

    asteroid2.dx = static_cast<float>(newVelocity2 * cos(newDirection2) + velocity2 * sin(direction2 - angle) * cos(angle + M_PI / 2));
    asteroid2.dy = static_cast<float>(newVelocity2 * sin(newDirection2) + velocity2 * sin(direction2 - angle) * sin(angle + M_PI / 2));
                                                                                                                                     
    float fx = asteroid1.x - asteroid2.x;
    float fy = asteroid1.y - asteroid2.y;

    float distance = std::sqrt(fx * fx + fy * fy);

    // Move the asteroids away from each other to avoid multiple collisions
    float overlap = asteroid1.radius + asteroid2.radius - distance;
    float moveX = overlap * cos(angle);
    float moveY = overlap * sin(angle);

    asteroid1.x = asteroid1.x + moveX / 2;
    asteroid1.y = asteroid1.y + moveY / 2;

    asteroid2.x = asteroid2.x - moveX / 2;
    asteroid2.y = asteroid2.y - moveY / 2;
}



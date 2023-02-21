#include "SpaceShip.h"

//void Ship::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
//{
//	
//}

void Ship::PoolEvent(SDL_Event& e)
{
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            //Adjust the velocity
            switch (e.key.keysym.sym)
            {
            case SDLK_UP: dy -= velocity; break;
            case SDLK_DOWN: dy += velocity; break;
            case SDLK_LEFT: dx -= velocity; break;
            case SDLK_RIGHT: dx += velocity; break;
            }
        }
        //If a key was released
        else if (e.type == SDL_KEYUP && e.key.repeat == 0)
        {
            //Adjust the velocity
            switch (e.key.keysym.sym)
            {
            case SDLK_UP: dy += velocity; break;
            case SDLK_DOWN: dy -= velocity; break;
            case SDLK_LEFT: dx += velocity; break;
            case SDLK_RIGHT: dx -= velocity; break;
            }
        }

}

void Ship::move()
{
    x += dx;
    y += dy;

    //If the dot went too far to the left or right
    if ((x < 0) || (x + getWidth() > 1000))
    {
        //Move back
        x -= dx;
    }


    //If the dot went too far up or down
    if ((y < 0) || (y + getHeight() > 600))
    {
        //Move back
        y -= dy;
    }

}

#include "SpaceShip.h"

//void Ship::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
//{
//	
//}

void Ship::PoolEvent(SDL_Event& e)
{
    //If a key was press
    if (e.type == SDL_KEYDOWN)
    {
        //Adjust the velocity
        if (e.key.keysym.sym == SDLK_UP)
        {
            keyUP = true;
        }
        if (e.key.keysym.sym == SDLK_DOWN)
        {
            keyDown = true;
        }
        if (e.key.keysym.sym == SDLK_LEFT)
        {
            keyLeft = true;
        }
        if (e.key.keysym.sym == SDLK_RIGHT)
        {
            keyRight = true;
        }
    }
    //If a key was released
    if (e.type == SDL_KEYUP)
    {
        if (e.key.keysym.sym == SDLK_UP)
        {
            keyUP = false;
        }
        if (e.key.keysym.sym == SDLK_DOWN)
        {
            keyDown = false;
        }
        if (e.key.keysym.sym == SDLK_LEFT)
        {
            keyLeft = false;
        }
        if (e.key.keysym.sym == SDLK_RIGHT)
        {
            keyRight = false;
        }
    }
}

void Ship::move(int width , int height)
{
    #pragma region moveShip
        if (keyUP == true)
            dy -= velocity;
        if (keyDown == true)
            dy += velocity;
        if (keyRight == true)
            dx += velocity;
        if (keyLeft == true)
            dx -= velocity;

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
    #pragma endregion

    teleport(width, height);
}

void Ship::teleport(float w_scrin, float h_scrin)
{
    if (x <= 0.0f)	x = x + (float)w_scrin;
    if (x >= (float)w_scrin)	x = x - (float)w_scrin;
    if (y <= 0.0f)	y = y + (float)h_scrin;
    if (y >= (float)h_scrin) y = y - (float)h_scrin;
}



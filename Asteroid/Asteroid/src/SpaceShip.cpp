#include "SpaceShip.h"

Ship::Ship(const char* path, SDL_Renderer* renderer)
    : Sprite(path, renderer)
{
    angleVelocity = 0;
    x = 0;
    y = 0;
}


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

void Ship::move(int width_S , int height_S)
{
    #pragma region moveShip
    if (keyUP == true)
        dy -= velocity;
    if (keyDown == true)
        dy += velocity;
    if (keyRight == true)
    {
        angleVelocity += velocity;
    }
    if (keyLeft == true)
    {
        angleVelocity -= velocity;
    }

        x += dx;
        y += dy;
        angle += angleVelocity;


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

        if (angleVelocity >= maxVelocity / 2)
            angleVelocity = maxVelocity / 2;
        else if (angleVelocity <= -maxVelocity / 2)
            angleVelocity = -maxVelocity / 2;
    #pragma endregion

}

void Ship::render(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    angle = this->angle;
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { static_cast<int>(x),  static_cast<int>(y), width, height };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
    float fx, fy;
    if (teleport(fx, fy, 1000, 1000))
    {
        
        SDL_Rect renderQuad2 = { static_cast<int>(fx),  static_cast<int>(fy), width, height };
        if (clip != NULL)
        {
            renderQuad2.w = clip->w;
            renderQuad2.h = clip->h;
        }
       
        SDL_RenderCopyEx(renderer, texture, clip, &renderQuad2, angle, center, SDL_FLIP_HORIZONTAL);
   /* x = fx;
    y = fy;*/
    }
   
    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, SDL_FLIP_HORIZONTAL);

   
    //Render to screen
    
    
}



bool Ship::teleport(float& ox, float& oy, int w_scrin, int h_scrin)
{
    bool isteleport = false;
    ox = x;
    oy = y;
    if (y < 0.0f)
    {
        oy = y + h_scrin;
         
        isteleport = true;
    }

    if (y + height >= h_scrin)
    {
        oy = y - h_scrin;
      
        isteleport = true;
    }

    if (x < 0.0f)
    {
        ox = x + w_scrin;
      
        isteleport =  true;
    }
    if (x + width >= w_scrin)
    {
        ox = x - w_scrin;
        isteleport = true;
    }
    x = ox;
    y = oy;
    return isteleport;
}



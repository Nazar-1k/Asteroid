#include "SpaceShip.h"
#include "Asteroid.h"

static Mix_Chunk* fireSound = nullptr;

Ship::Ship(const char* path, SDL_Renderer* renderer)
    : Sprite(path, renderer)
{
    x = 600;
    y = 300;

    //Initialize particles
    for (int i = 0; i < TOTAL_PARTICLES; ++i)
    {
        particles[i] = new Particle(x, y, width, angle, renderer);
    }

    //Load music
    fireSound = Mix_LoadWAV("soundEffects/fire.wav");
    if (fireSound == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

Ship::~Ship()
{
    //Delete particles
    for (int i = 0; i < TOTAL_PARTICLES; ++i)
    {
        delete particles[i];
    }

    Mix_FreeChunk(fireSound);

    fireSound = nullptr;
}


void Ship::PoolEvent(SDL_Event& e)
{
    switch (e.type)
    {
    //If a key was press
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            keyUP = true;
            break;
        case SDLK_DOWN:
            keyDown = true;
            break;
        case SDLK_LEFT:
            keyLeft = true;
            break;
        case SDLK_RIGHT:
            keyRight = true;
            break;
        }
        break;

    //If a key was released
    case SDL_KEYUP:
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                keyUP = false;
                break;
            case SDLK_DOWN:
                keyDown = false;
                break;
            case SDLK_LEFT:
                keyLeft = false;
                break;
            case SDLK_RIGHT:
                keyRight = false;
                break;
            }
        }
        break;
    }
}

void Ship::move()
{
    #pragma region moveShip
    if (keyUP == true)
    {
        dx += static_cast<float>(sin(angle * 3.14159 / 180) * velocity / 10);
        dy += static_cast<float>(-cos(angle * 3.14159 / 180) * velocity / 10);
        Mix_PlayChannel(-1, fireSound, 0);
    }
      /*  dy -= velocity;*/
    if (keyDown == true)
    {
        dy = 0;
        dx = 0;
    }
    if (keyRight == true)
    {
        angle += velocity * 5;
       
    }
    if (keyLeft == true)
    {
        angle -= velocity * 5;
     
    }
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

}

void Ship::render(SDL_Rect* clip, float angle, SDL_Point* center, SDL_RendererFlip flip)
{
    
        angle = this->angle;
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


        renderParticles();
    
}

void Ship::renderParticles()
{
    if (keyUP)
    {
        //Go through particles
        for (int i = 0; i < TOTAL_PARTICLES; ++i)
        {
            //Delete and replace dead particles
            if (particles[i]->isDead())
            {
                delete particles[i];
                particles[i] = new Particle(x, y, width, angle, renderer);
            }
        }

        //Show particles
        for (int i = 0; i < TOTAL_PARTICLES; ++i)
        {
            particles[i]->render();
        }
    }
    else
    {
        for (int i = 0; i < TOTAL_PARTICLES; ++i)
        {
            particles[i]->setdead(true);
        }
    }
}

bool Ship::colideAsteroid(Asteroid& ast)
{
    float fx = ast.x - x;
    float fy = ast.y - y;

    return  std::sqrt(fx * fx + fy * fy) <= ast.radius + width / 2;
}

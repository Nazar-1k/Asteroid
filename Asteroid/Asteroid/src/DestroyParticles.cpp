#include "DestroyParticles.h"

DestroyParticles::DestroyParticles(float x, float y, int side, SDL_Renderer* renderer)
    :time_out(false), x(x), y(y), side(side), renderer(renderer), out(false)
{
	//Initialize particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		particles[i] = new Particle(x, y, side, renderer);
	}
    timer = std::unique_ptr<Timer>(new Timer);
}

DestroyParticles::~DestroyParticles()
{
	//Delete particles
	for (int i = 0; i < TOTAL_PARTICLES; ++i)
	{
		delete particles[i];
	}
}

void DestroyParticles::render() 
{
    if (!out)
    {
        if (!time_out)
        {
            timer->start();
            time_out = true;
        }
        else if (time_out and timer->getTicks() - timer->isStarted() <= 300)
        {        
           
            int x = particles[1]->x;
            int y = particles[1]->y;
            //Show particles
            double angleIncrement = 2 * M_PI / TOTAL_PARTICLES;
            for (int i = 0; i < TOTAL_PARTICLES; ++i)
            {

                particles[i]->x += side * std::cos(i * angleIncrement);
                particles[i]->y += side * std::sin(i * angleIncrement);

                
                particles[i]->setAlfa(255-i*12);
                SDL_Delay(0.5);
                particles[i]->render();
            }
        }
        else
        {
            time_out = false;
            timer->stop();
            out = true;
        }
    }
}

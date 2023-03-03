#pragma once
#include "Particale.h"
#include "Timer.h"

class DestroyParticles
{
public:
	DestroyParticles(float x, float y, int side, SDL_Renderer* renderer);
	~DestroyParticles();

	void render();
	bool getOut() const { return out; }

private:
	float x, y, side;
	SDL_Renderer* renderer;

	//Particle count
	static const int TOTAL_PARTICLES = 20;
	//The particles
	Particle* particles[TOTAL_PARTICLES];

	std::unique_ptr<Timer> timer;
	bool time_out;
	bool out;
};


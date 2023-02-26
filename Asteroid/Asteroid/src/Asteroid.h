#pragma once

#include "Sprite.h"

class Asteroid : public Sprite
{
public:
	Asteroid(const char* path, SDL_Renderer* renderer);
	~Asteroid(){}

	void move();

	void render(SDL_Rect* clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:

	const float velocity = 2;
	const float maxVelocity = 8;

	float dx, dy;
	bool to_be_deleted;


	////Particle count
	//static const int TOTAL_PARTICLES = 20;
	////The particles
	//Particle* particles[TOTAL_PARTICLES];

	////Shows the particles
	//void renderParticles();

};

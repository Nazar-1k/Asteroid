#pragma once

#include "FireParticale.h"
#include <SDL_mixer.h>

class Asteroid;

class Ship : public Sprite
{
public:
	Ship(const char* path, SDL_Renderer* renderer);
	~Ship();
	void PoolEvent(SDL_Event& event);
	void move();

	void render(SDL_Rect* clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	bool colideAsteroid(Asteroid& ast);

private:
	bool keyUP = false;
	bool keyDown = false;
	bool keyRight = false;
	bool keyLeft = false;

	const float velocity = 1.5;
	const float maxVelocity = 8;

	float dx, dy;

	//Particle count
	static const int TOTAL_PARTICLES = 20;
	//The particles
	Particle* particles[TOTAL_PARTICLES];

	//Shows the particles
	void renderParticles();
	
};

#pragma once
#include "FireParticale.h"
#include <SDL_mixer.h>

class Ship : public Sprite
{
public:
	Ship();
	Ship(const char* path, SDL_Renderer* renderer);
	~Ship();
	void PoolEvent(SDL_Event& event);
	void moveArrow();
	void moveMouse();
	void move(int width, int height);

	void render(SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	bool teleport(float& ox, float& oy, int w_scrin, int h_scrin);

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

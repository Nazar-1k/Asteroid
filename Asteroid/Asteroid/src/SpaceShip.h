#pragma once

#include "Particale.h"
#include <SDL_mixer.h>
#include "Bullet.h"

class Asteroid;
class Arrow;


class Ship : public Sprite
{
public:
	Ship(const char* path, SDL_Renderer* renderer);
	~Ship();
	void PoolEvent(SDL_Event& event);
	void move();

	void render(SDL_Rect* clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void destroy() { is_active = false; }
	bool colideAsteroid(Asteroid& ast);

	friend void Bullet::creatBullet(Ship& Ship, Arrow& arrow);

private:
	bool keyUP = false;
	bool keyDown = false;
	bool keyRight = false;
	bool keyLeft = false;

	const float velocity = 1.5;
	const float maxVelocity = 8;

	float dx, dy;

	bool is_active;

	//Particle count
	static const int TOTAL_PARTICLES = 20;
	//The particles
	Particle* particles[TOTAL_PARTICLES];

	//Shows the particles
	void renderParticles();
	
};

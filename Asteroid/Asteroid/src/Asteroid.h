#pragma once

#include "Sprite.h"
#include "SpaceShip.h"

class Asteroid : public Sprite
{
public:
	Asteroid(float mass, const char* path, SDL_Renderer* renderer);
	~Asteroid() { }

	void move();
	void deleteAsteroid();

	void render(SDL_Rect* clip = NULL, float angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	static bool checkColition(Asteroid& asteroid1, Asteroid& asteroid2);
	static void reflectingAsteroids(Asteroid& asteroid1, Asteroid& asteroid2);

	friend bool Ship::colideAsteroid(Asteroid& ast);
	friend bool Bullet::colideAsteroid(Asteroid& ast);

private:
	float dx, dy;

	float mass;

	const float velocity = 2;
	const float maxVelocity = 4;

	float radius;
	bool to_be_deleted;

	//rotation left or right
	bool b_rotation;

	float speedrotation;

	////Particle count
	//static const int TOTAL_PARTICLES = 20;
	////The particles
	//Particle* particles[TOTAL_PARTICLES];

	////Shows the particles
	//void renderParticles();

};
